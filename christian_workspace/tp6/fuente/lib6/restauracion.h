/*
 * filtros.h
 *
 *  Created on: 16/05/2010`
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
void rb_ideal_notch(CImg<T> &H, int uc = 1, int vc = 1, int ancho = 1) {
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
	double distancia_pos = 0.0, distancia_neg = 0.0;
	int width = H.width();
	int height = H.height();
	H.normalize(0, 1);
	H.fill(1.0);

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

template<class T>
void rb_butter_notch(CImg<T> &H, int uc = 1, int vc = 1, int ancho = 1,
		int orden = 1) {
	H.normalize(0, 1);
	int width = H.width();
	int height = H.height();
	H.fill(0);
	double distancia_pos = 0.0, distancia_neg = 0.0, aux = 0.0;
	int mediox = width / 2, medioy = height / 2;

	cimg_forXY( H, x, y)
		{
			distancia_pos = sqrt(pow(x - mediox - uc, 2.0) + pow(y - medioy
					- vc, 2.0));
			distancia_neg = sqrt(pow(x - mediox + uc, 2.0) + pow(y - medioy
					+ vc, 2.0));
			aux = (ancho * ancho) / (distancia_pos * distancia_neg);
			H(x, y) = 1.0 / (1.0 + pow(aux, orden));
		}
}

template<class T>
void rb_gaussiano_notch(CImg<T> &H, int uc = 1, int vc = 1, int ancho = 1) {
	H.normalize(0, 1);
	H.fill(0);
	int width = H.width();
	int height = H.height();
	double distancia_pos = 0.0, distancia_neg = 0.0, aux = 0.0;
	int mediox = width / 2, medioy = height / 2;

	cimg_forXY( H, x, y)
		{
			distancia_pos = sqrt(pow(x - mediox - uc, 2.0) + pow(y - medioy
					- vc, 2.0));
			distancia_neg = sqrt(pow(x - mediox + uc, 2.0) + pow(y - medioy
					+ vc, 2.0));
			aux = (distancia_pos * distancia_neg) / (ancho * ancho);
			H(x, y) = 1.0 - exp((-1.0 / 2.0) * aux);
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
void ab_ideal_notch(CImg<T> &H_blanca, int uc = 1, int vc = 1, int ancho = 1) {
	/**H debe ser una imagen blanca
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir) ideal notch
	 */
	rb_ideal_notch(H_blanca, uc, vc, ancho);
	H_blanca = 1.0 - H_blanca;
}

template<class T>
void ab_butter_notch(CImg<T> &H_blanca, int uc = 1, int vc = 1, int ancho = 1,
		float orden = 1.0) {
	/**
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir) butter notch
	 */
	rb_butter_notch(H_blanca, uc, vc, ancho, orden);
	H_blanca = 1.0 - H_blanca;
}

template<class T>
void ab_gaussiano_notch(CImg<T> &H_blanca, int uc = 1, int vc = 1, int ancho =
		1) {
	/**
	 * retorna un filtro AB (pasa banda - acepta banda para no confundir) gaussiano notch
	 */
	rb_gaussiano_notch(H_blanca, uc, vc, ancho);
	H_blanca = 1.0 - H_blanca;
}

//ejercicio 5:
//fixme: esto no anda y me re podri!!! pagina 260 libro... formula d emodelado para sacar mov.
template<class T>
CImg<T> sacar_movimiento(CImg<T> imagen_movida, float t = 1.0, float a = 0.1,
		float b = 0.1) {
	/*//float pi = 3.14159;
	 CImgList<T> IMAGEN_MOVIDA = imagen_movida.get_FFT();
	 CImgList<T> H(IMAGEN_MOVIDA);
	 float tmp;
	 cimg_forXY(H[0],u,v)
	 {
	 tmp = 3.14159 * (u * a + v * b);
	 if (tmp != 0) {
	 H[0](u, v) = 1.0 / (t / tmp) * sin(tmp) * cos(1.0 * tmp);
	 H[1](u, v) = 1.0 / (t / tmp) * sin(tmp) * (-1.0 * sin(tmp));
	 }
	 }
	 //filtrar la imagen:

	 cimg_forXY(IMAGEN_MOVIDA[0],X,Y)
	 {
	 IMAGEN_MOVIDA[0](X, Y) *= H[0](X, Y);
	 IMAGEN_MOVIDA[1](X, Y) *= H[1](X, Y);
	 }
	 return IMAGEN_MOVIDA.get_FFT(true)[0];*/

}

template<class tipo>
CImg<tipo> dist_acumulada(CImg<tipo> img) {
	// Reduce ruido impulsivo en imagenes a color

	int M = img.width(), N = img.height();
	CImg<tipo> salida(img);
	double distancia, dmin;
	int xmin, ymin;
	tipo r, g, b, R, G, B;
	CImg_3x3(I,tipo);
	/*	para hacer un loop 3x3 automaticamente
	 I es la mascara
	 y por defecto en cada iteracion..Icc es el valor del centro
	 Icurrent current
	 Ipc=img(x-1,y)
	 previous current
	 Inn=img(x+1,y+1)...next next
	 asi tenes las 9 combinaciones
	 cualquiera de los dos modos define la mascara I
	 por ejemplo eso es la media aritmetica
	 el filtro
	 bueno dividido por 9*/
	cimg_for3x3(img,x,y,0,0,I,tipo)
		{
			if (x == 0 || x == M - 1 || y == 0 || y == N - 1)
				continue;
			R = img(x, y, 0), G = img(x, y, 1), B = img(x, y, 2);
			if (R != 0 && R != 1 && G != 0 && G != 1 && B != 0 && B != 1)
				continue; // no es impulsivo
			dmin = 1000;
			for (int i = -1; i <= 1; i++) { // recorro los 9 pixeles de la vecindad
				R = img(x - i, y - i, 0);
				G = img(x - i, y - i, 1);
				B = img(x - i, y - i, 2);
				for (int j = -1; j <= 1; j++) { // distancias de un pixel de la vecindad a todos los restantes de la vecindad
					r = img(x - j, y - j, 0);
					g = img(x - j, y - j, 1);
					b = img(x - j, y - j, 2);
					if (i == j)
						continue;
					distancia = (r - R) * (r - R) + (g - G) * (g - G) + (b - B)
							* (b - B);
					if (distancia < dmin) {
						dmin = distancia;
						xmin = x - j, ymin = y - j;
					}
				} //for j
			}// for i
			for (int c = 0; c < 3; c++)
				salida(x, y, c) = img(xmin, ymin, c);
		} //cimg_for
	return salida;
}
