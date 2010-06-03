/*
 * filtros.h
 *
 *  Created on: 07/05/2010
 *      Author: christian
 */
/*FUNCIONES PARA FILTRADO EN EL DOMINIO FRECUENCIAL
 * */

#include <CImg.h>
#include "../lib5/lib5.h"
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"
#include "../../../tp2/fuente/lib2/op_aritmeticos.h"
#include "figuras.h"

using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> filtrar_desde_tiempo(CImg<T> imagen_a_filtrar, CImg<T> h,
		CImg<T> &mag_H) {
	/* Filtra una imagen en el dominio de las frecuencias a partir de un filtro en el dominio espacial y de una imagen en el mismo
	 * dominio.
	 * (Esta funcion fue hecha con fines didacticos ya que sino simplemente se podria obtener le mismo resultado mediante conv.)
	 * Devuelve: la imagen filtrada y por referencia la magnitud del filtro
	 * @image_a_filtrar: imagen en el dominio espacial que se quiere filtrar
	 * @h: filtro espacial que se desea aplicar a la imagen
	 * @mag_H: Imagen del filtro centrada que se devuelve por referencia.. MagH debe ser de dimensiones = 2*imagen_a_filtrar
	 * */

	//agrandamos al doble el tam de la imagen rellenando con ceros en el espacio..:
	CImg<T> img_zeros = imagen_a_filtrar.get_resize(2
			* imagen_a_filtrar.width(), 2 * imagen_a_filtrar.height(), -100,
			-100, 0);
	//img_zeros.display();
	CImgList<T> IMG_ZEROS = img_zeros.get_FFT(); //obtengo fft de la imagen con el zeropadding

	CImg<T> h_zeros = h.get_resize(img_zeros.width(), img_zeros.height(), -100,
			-100, 0); //hago el zero padding en el filtro en el espacio
	CImgList<T> H_ZEROS = h_zeros.get_FFT(); //obtengo el filtro en frecuencia a traves de el H rellenado con ceros

	//aplicamos el filtro en frecuencia
	CImgList<T> imgfilt(mag_H, mag_H);

	cimg_forXY(H_ZEROS[0],x,y)
		{
			mag_H(x, y) = sqrt(pow(H_ZEROS[0](x, y), 2) + pow(H_ZEROS[1](x, y),
					2));

			imgfilt[0](x, y) = IMG_ZEROS[0](x, y) * mag_H(x, y);
			imgfilt[1](x, y) = IMG_ZEROS[1](x, y) * mag_H(x, y);
		}

	mag_H.shift(H_ZEROS[0].width() / 2, H_ZEROS[0].height() / 2, 0, 0, 2);//centramos el filtro para ser mostrado

	//calculamos la transformada inversa
	CImg<T> imgf = imgfilt.get_FFT(true)[0].crop(0, 0, imagen_a_filtrar.width()
			- 1, imagen_a_filtrar.height() - 1);
	return imgf;
}

template<class T>
CImg<T> filtrar(CImg<T> imagen, CImg<T> H) {
	/**
	 * Retorna la imagen filtrada con el filtro pasado
	 * El filtro debe estar diseñado no centrado y en frecuencia!!
	 */
	//imagen.shift(imagen.width()/2.0, imagen.height()/2.0, 0,0,2);
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	return F.get_FFT(true)[0]; //devuelvo la parte real
}

template<class T>
CImg<T> filtrar_complejo(CImg<T> img, CImgList<T> filtro) {
	/**by chaco...
	 * Retorna la imagen filtrada con el filtro pasado complejo
	 * El filtro debe estar diseñado centrado y
	 * FIXME: deberia estar el filtro shifteado???
	 */
	CImgList<T> tdf = img.get_FFT();

	filtro[0].shift(filtro[0].width() / 2, filtro[0].height() / 2, 0, 0, 2); //correcto?
	filtro[1].shift(filtro[1].width() / 2, filtro[1].height() / 2, 0, 0, 2); //correcto?

	cimg_forXY( img, x, y )
		{
			tdf[0](x, y) *= filtro[0](x, y);
			tdf[1](x, y) *= filtro[1](x, y);
		}
	return tdf.get_FFT(true)[0];
}
//######################################################################################
//######################################################################################
template<class T>
CImg<T> get_PB_ideal(int dimx, int dimy, float frec_corte = 10.0) {
	/* genera un PB ideal en frecuencia (H) con frec corte =10.0 por defecto de dimx x dimy*/
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	circulo_centrado<T> (H.width() / 2, H.height() / 2, H, frec_corte, 0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	return H;
}

template<class T>
CImg<T> get_PB_Butter(int dimx, int dimy, float frec_corte = 10.0, float orden =
		1.0) {
	//genera un filtro pasa bajos butterworth en frecuencia (H)  de dimx x dimy con frec corte =10 por defecto y orden 1.0 por defecto
	float distancia;
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(distancia / abs(frec_corte), 2.0 * abs(
					orden)));
		}
	return H;
}
template<class T>
CImg<T> get_PB_gauss(int dimx, int dimy, float varianza = 1.0) {
	//genera un filtro gaussiano  en frecuencia (H)
	float distancia;
	CImg<T> H(dimx, dimy, 1, 1, 0);
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = exp((-1.0 * pow(distancia, 2.0)) / (2.0
					* pow(varianza, 2)));
		}
	return H;
}

template<class T>
CImg<T> get_PA_ideal(int dimx, int dimy, float frec_corte = 10.0) {
	/* genera un PA ideal  en frecuencia (H) con frec corte =10.0 por defecto de dimx x dimy*/
	CImg<T> H(dimx, dimy, 1, 1);
	circulo_centrado_inverso<T> (H.width() / 2, H.height() / 2, H, frec_corte,
			0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	return H;
}

template<class T>
CImg<T> get_PA_Butter(int dimx, int dimy, float frec_corte = 10.0, float orden =
		1.0) {
	//genera un filtro pasa altos butterworth  en frecuencia (H) de dimx x dimy con frec corte =10 por defecto y orden 1.0 por defecto
	float distancia;
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	CImg<T> H(dimx, dimy, 1, 1, 0.0);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(abs(frec_corte) / distancia, 2.0 * abs(
					orden)));
		}
	return H;
}
template<class T>
CImg<T> get_PA_gauss(int dimx, int dimy, float varianza = 1.0) {
	//genera un filtro PA gaussiano  en frecuencia (H) con varianza 1.0 por defecto
	float distancia;
	CImg<T> H(dimx, dimy, 1, 1, 0);
	float mediox = dimx / 2.0;
	float medioy = dimy / 2.0;
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 - exp((-1.0 * pow(distancia, 2.0)) / (2.0 * pow(
					varianza, 2)));
		}
	return H;
}
//######################################################################################
//######################################################################################
template<class T>
CImg<T> aplicar_PB_ideal(CImg<T> imagen, float frec_corte = 10.0) {
	/*aplica un filtro pasa Bajos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H = get_PB_ideal<T> (imagen.width(), imagen.height(), frec_corte);
	return filtrar<T> (imagen, H);
}

template<class T>
CImg<T> aplicar_PB_Butter(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/* aplica un filtro pasa Bajos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	H = get_PB_Butter<T> (imagen.width(), imagen.height(), frec_corte, orden);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	//return filtrar<T> (imagen, Hf);
	return filtrar_M(imagen, H, true); //esta es la de M -> ojo si no anda comentarla y usar la otra de arriba

}

template<class T>
CImg<T> H_to_h(CImg<T> H, bool centrada = true) {
	if (centrada) {
		return H.get_FFT(true)[0].shift(H.width() / 2.0, H.height() / 2.0, 0,
				0, 2);
	} else
		return H.get_FFT(true)[0];
}

template<class T>
CImg<T> aplicar_PB_Gaussiano(CImg<T> imagen, CImg<T> &H, float varianza = 1.0) {
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	H = get_PB_gauss<T> (imagen.width(), imagen.height(), varianza);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	return filtrar<T> (imagen, Hf);
}

/*##########################################################################################
 * ##########################################################################################*/

/*FILTROS PASA ALTOS PARA EJERCICIO 4 -
 * */
// FILTROS DEFINIDOS EN FRECUENCIA:
template<class T>
CImg<T> aplicar_PA_ideal(CImg<T> imagen, float frec_corte = 10.0) {
	/*aplica un filtro pasa Altos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H(imagen.width(), imagen.height(), 1, 1, 1.0);
	H = get_PA_ideal<T> (imagen.width(), imagen.height(), frec_corte);
	return filtrar<T> (imagen, H);
}

template<class T>
CImg<T> aplicar_PA_Butter(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/*aplica un filtro pasa Altos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	H = get_PA_Butter<T> (imagen.width(), imagen.height(), frec_corte, orden);
	CImg<T> Hf = H.get_shift(H.width() / 2, H.height() / 2, 0, 0, 2); //vuelvo a la original para ver el filtro centrado
	return filtrar<T> (imagen, Hf);
}

template<class T>
CImg<T> aplicar_PA_Gaussiano(CImg<T> imagen, CImg<T> &H, float varianza = 1.0) {
	/*aplica un filtro pasa Altos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	H = get_PA_gauss<T> (imagen.width(), imagen.height(), varianza);
	CImg<T> Hf = H.get_shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2.0);
	return filtrar<T> (imagen, Hf);
}

//##########################################################################################

template<class T>
CImg<T> to_log(CImg<T> &img) {
	/**
	 * Aplicado de logaritmo teniendo en cuenta valores negativos
	 * log = log(1+img(x,y))
	 */
	cimg_forXY(img,x,y)
		{
			img(x, y) = log(1 + img(x, y));
		}
	return img;
}

template<class T, class U>
U d2 ( T x, T y, U x0, U y0 ) {
	/**
	 * distancia euclídea
	 */
  return sqrt( pow((U)x-x0,2.0)+pow((U)y-y0,2.0) );
}

template<class T>
CImg<T> get_homomorfico(short w, short h, T gl, T gh, T D0, T c = (T) 2.0,
		bool centrar = true) {
	//devuelve un filtro del tipo homomorfico...
	CImg<T> H(w, h, 1, 1, (T) 0);
	unsigned x, y;
	T cx = w / 2.0, cy = h / 2.0;
	cimg_forXY( H, x, y )
		{
			H(x, y) = (gh - gl) * (1 - exp(-c * (d2(x, y, cx, cy)
					/ pow(D0, 2.0)))) + gl;
		}
	if (!centrar)
		return H.shift(w / 2, h / 2, 0, 0, 2);
	return H;
}

template<class T>
CImg<T> aplicar_filtro_homomorfico(const CImg<T> &imag, T gl, T gh, T D0, T c =
		(T) 2.0) {
	/* Retorna la imagen con filtrado Homomorfico
	 * pasos: f(x,y) -> log{} -> F{} -> H*F(u,v) -> Finv.{} -> exp{} -> g(x,y)
	 1_    ____gh   1_ _---gh   1_    _-    gh
	 *    |  _-          |_-         |  _-
	 * gl |_-            |           |_-
	 *    |_________     |________   |_________
	 *
	 *     0 < gl < 1    gh > 1
	 *
	 * gl   0 < gl < 1
	 *   a >gl =>  mas  brillo medio (deja pasar  mas  bajas frec)
	 *   a <gl => menos brillo medio (deja pasar menos bajas frec)
	 * gh   gh > 1
	 *   a >gh =>  mas  contraste ( aumenta  mas  las altas frec )
	 *   a <gh => menos contraste ( aumenta menos las altas frec)
	 */

	short w = imag.width(), h = imag.height();
	CImgList<T> fft = (imag.get_channel(0) + 1.0).get_log().get_FFT();
	CImg<T> filtro = get_homomorfico(w, h, gl, gh, D0, c, false);
	fft = realimag2magfase(fft);
	cimg_forXY( filtro, x, y )
		{
			fft[0](x, y) *= filtro(x, y);
		}

	fft = magfase2realimag(fft);

	return fft.get_FFT(true)[0].exp();
}
/*################## FILTRADO ALTA POTENCIA #############################*/

template<class T>
CImg<T> aplicar_filtro_alta_potencia(const CImg<T> &filtro_pa, T A) {
	/**
	 * filtro alta potencia
	 */
	return CImg<T> (filtro_pa + (A - 1.0));
}

/*################## ENFASIS ALTA FRECUENCIA #############################*/
template<class T>
CImg<T> aplicar_filtro_eaf(const CImg<T> &filtro_pa, T a, T b) {
	/**
	 * filtro énfasis de alta frecuencia
	 */
	return CImg<T> (((filtro_pa * b) + a));
}

