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
using namespace std;
using namespace cimg_library;

template<class T>
CImg<T> aplicar_PB_ideal(CImg<T> imagen, int frec_corte = 10) {
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
CImg<T> aplicar_Butter_PB(CImg<T> imagen, CImg<T> &H, int frec_corte = 10,
		int orden = 1) {
	/*aplica un filtro pasa Bajos Butterwortch con frecuencia de corte: frec_corte y orden = orden.
	 * Por defecto: frec_corte=10 y orden=1
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro...
	 */
	float distancia;
	float mediox = imagen.width() / 2.0;
	float medioy = imagen.height() / 2.0;
	//CImg<T> H(imagen.width(), imagen.height(), 1, 1);
	cimg_forXY(H,x,y)
		{
			distancia = sqrt(pow(x - mediox, 2.0) + pow(y - medioy, 2.0));
			H(x, y) = 1.0 / (1.0 + pow(distancia / abs(frec_corte), 2.0 * abs(
					orden)));
		}
	//H.normalize(0.0, 1.0);
	//H.shift(H.width() / 2, H.height() / 2, 0, 0, 2); //centro la func de transferencia
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
CImg<T> aplicar_Gaussiano_PB(CImg<T> imagen, CImg<T> &H, float sigma = 1.0) {
	/*aplica un filtro pasa Bajos Gaussiano con varianza=sigma
	 * Devuelve la imagen filtrada para ser mostrada.
	 * devuelve por referencia H para poder plotear el filtro
	 * solo andaa para datos del tipo DOUBLE!!
	 * */
	CImg<T> h = gaussian_mask(imagen.width(), sigma); //filtro gaussiando pasa bajos espacial
	CImgList<T> H_FFT = h.get_FFT(); //obtengo la respuesta en frecuencia del filtro gaussiano
	cimglist_apply(H_FFT, shift)(imagen.width() / 2, imagen.height() / 2, 0, 0, 2);

	CImg<T> H_real = H_FFT[0];
	H=H_real;
	CImg<T> H_imag = H_FFT[1];

	CImgList<T> IMAGEN_FFT = imagen.get_FFT();
	CImg<T> IMAGEN_real = IMAGEN_FFT[0];
	CImg<T> IMAGEN_imag = IMAGEN_FFT[1];

	IMAGEN_real = multiplicar<T> (IMAGEN_real, H_real, false);
	IMAGEN_imag = multiplicar<T> (IMAGEN_imag, H_imag, false);
	IMAGEN_FFT[0] = IMAGEN_real;
	IMAGEN_FFT[1] = IMAGEN_imag;
	return IMAGEN_FFT.get_FFT(true)[0]; //devuelvo la parte real
}
