/*
 * filtros.h
 *
 *  Created on: 07/05/2010
 *      Author: christian
 */
/*FUNCIONES PARA FILTRADO EN EL DOMINIO FRECUENCIAL
 * */

#include <CImg.h>
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

#include "../../../tp2/fuente/lib2/op_aritmeticos.h"
#include "figuras.h"

using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> filtrar(CImg<T> img, CImg<T> filtro) {
	/**
	 * Retorna la imagen filtrada con el filtro pasado
	 * El filtro debe estar diseñado centrado
	 */
	CImgList<T> tdf = img.get_FFT();
	filtro.shift(filtro.width() / 2, filtro.height() / 2, 0, 0, 2);
	cimg_forXY( filtro, x, y )
		{
			tdf[0](x, y) *= filtro(x, y);
			tdf[1](x, y) *= filtro(x, y);
		}

	return tdf.get_FFT(true)[0];
}
// FILTROS DEFINIDOS EN FRECUENCIA:
template<class T>
CImg<T> aplicar_PB_ideal(CImg<T> imagen, float frec_corte = 10.0) {
	/*aplica un filtro pasa Bajos IDEAL centrado de radio=frec_corte. Por defecto 10. (muy selectivo)
	 * Devuelve la imagen filtrada para ser mostrada.
	 */
	CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	circulo_centrado<T> (H.width() / 2, H.height() / 2, H, frec_corte, 0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
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
CImg<T> aplicar_Butter_PB(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/*aplica un filtro pasa Bajos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	float distancia;
	float mediox = imagen.width() / 2.0;
	float medioy = imagen.height() / 2.0;
	//creo el filtro...
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(distancia / abs(frec_corte), 2.0 * abs(
					orden)));
		}
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); // para filtrar...
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //vuelvo a la original para ver el filtro centrado
	return F.get_FFT(true)[0]; //devuelvo la parte real
}

template<class T>
CImg<T> aplicar_Gaussiano_PB_def_frec(CImg<T> imagen, CImg<T> &H,
		float varianza = 1.0) {
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	float distancia;
	float mediox = imagen.width() / 2.0;
	float medioy = imagen.height() / 2.0;
	//CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = exp((-1.0 * pow(distancia, 2.0)) / (2.0
					* pow(varianza, 2)));
		}
	//H.normalize(0.0, 1.0);
	//H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	H.shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	H.shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2); //esto es para que se vea centrado cuando lo devuelvo por referencia
	return F.get_FFT(true)[0]; //devuelvo la parte real
}

//FILTROS DEFINIDOS EN TIEMPO Y CONVERTIDOS A FRECUENCIA
template<class T>
CImg<T> aplicar_Gaussiano_PB(CImg<T> imagen, CImg<T> &H, float sigma = 1.0) {
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	//fixme: esta funcion no anda!
	CImg<T> h = gaussian_mask(imagen.width(), sigma); //filtro gaussiando pasa bajos espacial
	CImgList<T> H_FFT = h.get_FFT(); //obtengo la respuesta en frecuencia del filtro gaussiano
	/*	cimglist_apply(H_FFT, shift)
	 (imagen.width() / 2, imagen.height() / 2, 0, 0, 2);*/
	CImg<T> H_real = H_FFT[0];
	H = H_real;
	H_real.shift(h.height() / 2.0, H.width() / 2.0, 0, 0, 2);
	imagen.shift(imagen.width() / 2, imagen.height() / 2, 0, 0, 2);
	//H_real.shift(H_real.width() / 2, H_real.height() / 2, 0, 0, 2); //descentro para palicarselo a la iamgen

	CImgList<T> IMAGEN_FFT = imagen.get_FFT();
	CImg<T> IMAGEN_real = IMAGEN_FFT[0];
	CImg<T> IMAGEN_imag = IMAGEN_FFT[1];

	IMAGEN_real = multiplicar<T> (IMAGEN_real, H_real, false);
	IMAGEN_imag = multiplicar<T> (IMAGEN_imag, H_real, false); //fixme: la parte imaginaria la multiplico por la parte real de la funcion de transferencia... esta bien esto?
	cimg_forXY(IMAGEN_FFT[0],X,Y)
		{
			IMAGEN_FFT[0](X, Y) = IMAGEN_real(X, Y);
			IMAGEN_FFT[1](X, Y) = IMAGEN_imag(X, Y);
		}
	return IMAGEN_FFT.get_FFT(true)[0]; //devuelvo la parte real
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
	CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	circulo_centrado_inverso<T> (H.width() / 2, H.height() / 2, H, frec_corte, 0); //creo la mascara
	H.normalize(0.0, 1.0);
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
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
CImg<T> aplicar_Butter_PA(CImg<T> imagen, CImg<T> &H, float frec_corte = 10.0,
		float orden = 1.0) {
	/*aplica un filtro pasa Altos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	float distancia;
	float mediox = imagen.width() / 2.0;
	float medioy = imagen.height() / 2.0;
	//creo el filtro...
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(abs(frec_corte)/distancia, 2.0 * abs(
					orden)));
		}
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); // para filtrar...
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //vuelvo a la original para ver el filtro centrado
	return F.get_FFT(true)[0]; //devuelvo la parte real
}

template<class T>
CImg<T> aplicar_Gaussiano_PA_def_frec(CImg<T> imagen, CImg<T> &H,
		float varianza = 1.0) {
	/*aplica un filtro pasa Altos Gaussiano con varianza=sigma (DEFINIDO EN FRECUENCIA)
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	float distancia;
	float mediox = imagen.width() / 2.0;
	float medioy = imagen.height() / 2.0;
	//CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0-exp((-1.0 * pow(distancia, 2.0)) / (2.0
					* pow(varianza, 2)));
		}
	//H.normalize(0.0, 1.0);
	//H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
	CImgList<T> F = imagen.get_FFT();//obtengo la transformada
	CImg<T> F_real = F[0]; //parte real
	CImg<T> F_imag = F[1]; //parte imaginaria
	//realizo el filtrado en el dominio de las frecuecnias:
	H.shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2);
	F_real = multiplicar<T> (F_real, H, false);
	F_imag = multiplicar<T> (F_imag, H, false);
	F[0] = F_real;
	F[1] = F_imag;
	H.shift(H.width() / 2.0, H.height() / 2.0, 0, 0, 2); //esto es para que se vea centrado cuando lo devuelvo por referencia
	return F.get_FFT(true)[0]; //devuelvo la parte real
}

//FILTROS DEFINIDOS EN TIEMPO Y CONVERTIDOS A FRECUENCIA
template<class T>
CImg<T> aplicar_Gaussiano_PA(CImg<T> imagen, CImg<T> &H, float sigma = 1.0) {
	/*aplica un filtro pasa Altos Gaussiano con varianza=sigma
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	CImg<T> h = gaussian_mask(imagen.width(), sigma); //filtro gaussiando pasa bajos espacial
	CImgList<T> H_FFT = h.get_FFT(); //obtengo la respuesta en frecuencia del filtro gaussiano
	/*	cimglist_apply(H_FFT, shift)
	 (imagen.width() / 2, imagen.height() / 2, 0, 0, 2);*/
	CImg<T> H_real = H_FFT[0];
	cimg_forXY(H_real, x,y){
		H_real(x,y)=1.0-H_real(x,y); // lo paso a Pasa altos
	}
	H = H_real;
	//h.shift(h.height() / 2.0, H.width() / 2.0, 0, 0, 2); //todo: para que cuerno hago esto? revisar...
	imagen.shift(imagen.width() / 2, imagen.height() / 2, 0, 0, 2);
	//H_real.shift(H_real.width() / 2, H_real.height() / 2, 0, 0, 2); //descentro para palicarselo a la iamgen

	CImgList<T> IMAGEN_FFT = imagen.get_FFT();
	CImg<T> IMAGEN_real = IMAGEN_FFT[0];
	CImg<T> IMAGEN_imag = IMAGEN_FFT[1];

	IMAGEN_real = multiplicar<T> (IMAGEN_real, H_real, false);
	IMAGEN_imag = multiplicar<T> (IMAGEN_imag, H_real, false); //fixme: la parte imaginaria la multiplico por la parte real de la funcion de transferencia... esta bien esto?
	cimg_forXY(IMAGEN_FFT[0],X,Y)
		{
			IMAGEN_FFT[0](X, Y) = IMAGEN_real(X, Y);
			IMAGEN_FFT[1](X, Y) = IMAGEN_imag(X, Y);
		}
	return IMAGEN_FFT.get_FFT(true)[0]; //devuelvo la parte real
}
