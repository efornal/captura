/*
 * filtros.h
 *
 *  Created on: 16/05/2010
 *      Author: christian
 */

#include <CImg.h>
using namespace std;
using namespace cimg_library;

// ==========================================================
//                        ruido
// ==========================================================
/*
 * noice: Add random noise to the values of the instance image.
 *
 * Parameters:
 *   - sigma      Amplitude of the random additive noise.
 *                If sigma<0, it stands for a percentage of the global value range.
 *
 *   - noise_type Type of additive noise
 *                0 = gaussian,
 *                1 = uniform,
 *                2 = Salt and Pepper,
 *                3 = Poisson
 *                4 = Rician
 */
template<class T>
void gen_ruido_gaussiano(CImg<T> &img, double sigma = 1.0) {
	/**
	 * Genera ruido gausiano en la imagen dada
	 */
	img.noise(sigma, 0); // gaussian = 0
}

template<class T>
void gen_ruido_uniforme(CImg<T> &img, double sigma = 1.0) {
	/**
	 * Genera ruido uniforme en la imagen dada
	 */
	img.noise(sigma, 1);
}

template<class T>
void gen_ruido_sal_y_pimienta(CImg<T> &img, double sigma = 1.0) {
	/**
	 * Genera ruido sal y pimienta en la imagen dada
	 */
	img.noise(sigma, 2);
}

template<class T>
void gen_ruido_sal(CImg<T> &img, double sigma = 1.0) {
	/**
	 * Genera ruido sal (unicamente) en la imagen dada
	 */
	CImg<T> ruido(img.width(), img.height(), 1, 1, 0);
	ruido.noise(sigma, 2);
	cimg_forXY(img,x,y)
		{
			if (ruido(x, y))
				img(x, y) = 255;
		}
}

template<class T>
void gen_ruido_pimienta(CImg<T> &img, double sigma = 1.0) {
	/**
	 * Genera ruido pimienta (unicamente) en la imagen dada
	 */
	CImg<T> ruido(img.width(), img.height(), 1, 1, 0);
	ruido.noise(sigma, 2);
	cimg_forXY(img,x,y)
		{
			if (ruido(x, y))
				img(x, y) = 0;
		}
}

//====================================================
//                filtros espaciales
//====================================================


template<class T>
CImg<T> filtrado_geometrica(CImg<T> img, int size = 3) {
	/**
	 * retorna un filtro espacial de media geometrica
	 * @size Tamanio de la mascara
	 * formula:
	 *   f'(x,y) = [ prod{ g(x,y) } ] ^ (1/mn)
	 */
	CImg<T> mask(size, size, 1, 1, 0);
	CImg<T> filtrada(img);
	double prod;
	int mid = size / 2;

	cimg_forXY(img,x,y)
		{
			prod = 1.0;

			mask = img.get_crop(x - mid, y - mid, x + mid, y + mid, true);
			cimg_forXY(mask,s,t)
				{
					prod *= mask(s, t);
				}
			filtrada(x, y) = pow(prod, (1.0 / (size * size)));
		}

	return filtrada;
}

template<class T>
CImg<T> filtrado_contra_armonica(CImg<T> img, float q = 0.0, int size = 3) {
	/**
	 * retorna un filtro espacial de media contra-armonica
	 * @q Orden del filtro
	 * @size Tamanio de la mascara
	 * formula:
	 *              sum{ g(x,y)^q+1 }
	 *   f'(x,y) =  -----------------
	 *               sum{ g(x,y)^q }
	 */
	CImg<T> mask(size, size, 1, 1, 0);
	CImg<T> filtrada(img);
	double suma_qn, suma_qd; // suma q numerador / denominador
	int mid = size / 2;

	cimg_forXY(img,x,y)
		{
			suma_qn = 0.0;
			suma_qd = 0.0;
			mask = img.get_crop(x - mid, y - mid, x + mid, y + mid, true);
			cimg_forXY(mask,s,t)
				{
					suma_qn += pow(mask(s, t), q + 1);
					suma_qd += pow(mask(s, t), q);
				}
			filtrada(x, y) = suma_qn / suma_qd;
		}

	return filtrada;
}

template<class T>
CImg<T> filtrado_mediana(CImg<T> img, int size = 3) {
	/**
	 * retorna un filtro espacial de orden, mediana
	 * @size Tamanio de la mascara
	 * formula:
	 *   f'(x,y) =  mediana { g(x,y) }
	 */
	CImg<T> mask(size, size, 1, 1, 0);
	CImg<T> filtrada(img);
	int mid = size / 2;

	cimg_forXY(img,x,y)
		{
			mask = img.get_crop(x - mid, y - mid, x + mid, y + mid, true);
			filtrada(x, y) = mask.median();
		}

	return filtrada;
}

template<class T>
CImg<T> filtrado_punto_medio(CImg<T> img, int size = 3) {
	/**
	 * retorna un filtro espacial de orden, punto medio
	 * @size Tamanio de la mascara
	 * formula:
	 *   f'(x,y) =  1/2 * [ MAX{g(x,y)} + MIN{g(x,y)} ]
	 */
	CImg<T> mask(size, size, 1, 1, 0);
	CImg<T> filtrada(img);
	int mid = size / 2;

	cimg_forXY(img,x,y)
		{
			mask = img.get_crop(x - mid, y - mid, x + mid, y + mid, true);
			filtrada(x, y) = (1.0 / 2.0) * (mask.min() + mask.max());
		}

	return filtrada;
}

template<class T>
CImg<T> filtrado_alfa_recortado(CImg<T> img, int d = 0, int size = 3) {
	/**
	 * retorna un filtro espacial de orden, alfa recortado
	 * @size Tamanio de la mascara
	 * formula:
	 *                 1
	 *   f'(x,y) =    ---  SUM{ gr(x,y) }     0 <= d <= mn-1
	 *                mn-d
	 *
	 *                       si d=0    => media aritmetica
	 *                       si d=mn-1 => mediana
	 *
	 * Ej: dada la mask[1 5 2 .. 3] nxn(filasXcolumnas) con coef a0..anxn,
	 * arma la lista:
	 *              lis = [a0,a1,...ak]    donde k = m*n
	 * luego lo ordena:
	 *             liso = [1 2 3,...ak]
	 * luego calcula gr(x,y) = SUM{ liso(d), liso(d+1),.. liso(k-d) }
	 *  sumatoria desde d/2 hasta nm-d/2.
	 * finalmente calcula f' como dice arriba
	 */
	CImg<T> mask(size, size, 1, 1, 0);
	CImg<T> filtrada(img);
	int mid = size / 2, cont = 0;
	double suma = 0.0;
	CImg<T> lista(size * size, 1, 1, 1, 0);

	cimg_forXY(img,x,y)
		{
			mask = img.get_crop(x - mid, y - mid, x + mid, y + mid, true);
			cont = 0, suma = 0.0;
			cimg_forXY(mask,s,t)
				{
					lista(cont++, 0) = mask(s, t);
				}
			lista.sort(true); // bool increasing=true (creciente)
			for (int i = d / 2; i < (size * size - d / 2); i++) {
				suma += lista(i);
			}
			filtrada(x, y) = (1.0 / (size * size - d)) * suma;
		}

	return filtrada;
}
//####################################################################################
//####################################################################################

//filtros para aplicar en el dominio frecuencial:
// ============================================================
//                     Rechaza Banda
// ============================================================

template<class T>
void rb_ideal(CImg<T> &H, int wc = 1, int espesor = 1) {
	/**
	 * retorna por referencia un filtro RB (rechaza banda) ideal
	 * @espesor: espesor de la linea del filtro -> mayor espesor + rechaza.
	 * @wc: frecuencia de corte o radio del circulo de rechazo.
	 */
	H.normalize(0, 1);
	int width = H.width();
	int height = H.height();
	double rechazo[] = { 0.0, 0.0, 0.0 };
	double paso[] = { 1.0, 1.0, 1.0 };
	H.fill(1.0);
	H.draw_circle(width / 2, height / 2, wc + espesor / 2, rechazo);
	H.draw_circle(width / 2, height / 2, wc - espesor / 2, paso);
}

template<class T>
void rb_butter(CImg<T> &H, int wc = 1, int ancho = 1, int orden = 1) {
	/**
	 * retorna un filtro RB (rechaza banda) butterworth
	 * formula:
	 *                      1
	 *   H(u,v) = ----------------------
	 *            1 + [ D*W / D^2-wc^2 ]
	 *
	 * D  = distancia de cada punto al origen
	 * wc = frecuencia de corte
	 * W  = @ancho= espesor del filtro
	 * aux =  [ D*W / D^2-wc^2 ]
	 */
	int width = H.width();
	int height = H.height();
	H.normalize(0, 1);
	H.fill(0.0);
	double distancia = 0.0, aux = 0.0;
	int mediox = width / 2, medioy = height / 2;

	cimg_forXY( H, x, y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			aux = (ancho * distancia) / (pow(distancia, 2) - pow(wc, 2));
			H(x, y) = 1.0 / (1.0 + pow(aux, 2.0 * orden));
		}
}

template<class T>
void rb_gaussiano(CImg<T> &H, int wc = 1, int ancho = 1) {
	/**
	 * retorna un filtro RB (rechaza banda) gaussiano
	 * formula:
	 *                  (-1/2) * [ D^2-wc^2 / DW  ]
	 *   H(u,v) = 1 - e
	 *
	 *
	 * D  = distancia de cada punto al origen
	 * wc = frecuencia de corte
	 * W  = ancho del filtro
	 * aux =   [ D^2-wc^2 / DW  ]
	 */
	int width = H.width();
	int height = H.height();
	H.normalize(0, 1);
	H.fill(0.0);
	double distancia = 0.0, aux = 0.0;
	int mediox = width / 2, medioy = height / 2;

	cimg_forXY( H, x, y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			aux = (pow(distancia, 2) - pow(wc, 2)) / (distancia * ancho);
			H(x, y) = 1.0 - exp((-1.0 / 2.0) * pow(aux, 2));
		}
}

template<class T>
void rb_ideal_notch(CImg<T>&H, int uc = 1, int vc = 1, int ancho = 1) {
	/**
	 * retorna un filtro RB (rechaza banda) ideal notch
	 * formula:
	 *            | 0   si D1(u,v) <= D0  || D2(u,v) <= D0
	 *   H(u,v) = |
	 *            | 1   otro caso
	 *
	 * D1 = distancia de cada punto al centro positivo del notch (u0,v0)
	 * D2 = distancia de cada punto al centro negativo del notch (-u0,-v0)
	 * uc = frecuencia de corte
	 * vc = frecuencia de corte
	 *      mas que frecuencia de corte es frecuencia (u0,v0) eliminada
	 * W  = ancho del filtro (radio del notch, del origen u0,v0)
	 */
	int width = H.width();
	int height = H.height();
	H.normalize(0, 1);
	H.fill(1.0);
	double distancia_pos = 0.0, distancia_neg = 0.0;
	int mediox = width / 2, medioy = height / 2;

	cimg_forXY( H, x, y)
		{
			distancia_pos = sqrt(pow(x - mediox - uc, 2.0) + pow(y - medioy
					- vc, 2.0));
			distancia_neg = sqrt(pow(x - mediox + uc, 2.0) + pow(y - medioy
					+ vc, 2.0));
			if (distancia_pos <= ancho || distancia_neg <= ancho) {
				H(x, y) = 0;
			}
		}
}

// ============================================================
//                     Pasa Banda
// ============================================================

template<class T>
void ab_ideal(CImg<T> &H, int wc = 1, int ancho = 1) {
	/**
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir cpn pasa bajos (PB)) ideal
	 */
	H.normalize(0, 1);
	rb_ideal(H, wc, ancho);
	H = 1.0 - H;
}

template<class T>
void ab_butter(CImg<T> &H, int wc = 1, int ancho = 1, int orden = 1) {
	/**
	 * retorna un filtro AB (acepta banda) butterworth
	 */
	rb_butter(H, wc, ancho, orden);
	H = 1.0 - H;
}

template<class T>
void ab_gaussiano(CImg<T> &H, int wc = 1, int ancho = 1) {
	/**
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir) gaussiano
	 */
	rb_gaussiano(H, wc, ancho);
	H = 1.0 - H;
}

template<class T>
void ab_ideal_notch(CImg<T> &H, int uc = 1, int vc = 1, int ancho = 1) {
	/**
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir) ideal notch
	 */
	rb_ideal_notch(H, uc, vc, ancho);
	H = 1.0 - H;
}
