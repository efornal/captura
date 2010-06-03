/*
 * lib5.h
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <complex>
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;
template<class T>
CImg<T> get_fase(CImg<T> imagen) {
	/*devuelve la fase de la transformada de fourier
	 * */
	CImgList<T> tdf = imagen.get_FFT(); //obtengo la fft
	CImg<T> real = tdf[0];
	CImg<T> imag = tdf[1];

	complex<T> I(0., 1.); //definicion de la constatnte imaginaria I=sqrt(-1)
	CImg<T> fase(imagen.width(), imagen.height(), 1, 1);

	for (int i = 0; i < imagen.width(); i++) {
		for (int j = 0; j < imagen.height(); j++) {
			complex<T> complejo = real(i, j) + I * imag(i, j);
			fase(i, j) = arg(complejo);
		}
	}
	return fase;
}

template<class T>
CImg<T> get_magnitud(CImg<T> imagen, bool centrar = false) {
	//devuelve la magnitud de la transformada de fourier... (resp en frecuencia)
	// por defecto no centrada...
	CImgList<T> tdf = imagen.get_FFT(); //obtengo la fft
	CImg<T> real = tdf[0];
	CImg<T> imag = tdf[1];

	CImg<T> magnitud(imagen.width(), imagen.height(), 1, 1);

	for (int i = 0; i < imagen.width(); i++) {
		for (int j = 0; j < imagen.height(); j++) {
			magnitud(i, j) = sqrt(pow(real(i, j), 2.0) + pow(imag(i, j), 2.0));
		}
	}
	if (centrar) {
		magnitud.shift(magnitud.width() / 2.0, magnitud.height() / 2.0, 0, 0, 2);
	}
	return magnitud;
}

template<class T>
CImg<T> get_imagen_solo_magnitud(CImg<T> imagen) {
	//devuelve la imagen reconstrudia con solo la magnitud

	//fixme: estara bien esto che?
	//devuelve la imagen con solo la magnitud (o sea fase=0)
	// OJO DEVUELVE SOLO LA PARTE CON VALORES REALES DE LA IMAGEN...
	CImgList<> TDF_imagen = imagen.get_FFT(); //me devuelve la fft

	CImg<T> magni = get_magnitud<T> (imagen);

	cimg_forXY(magni, x, y) //recorro las imaginarias
		{
			TDF_imagen[0](x, y) = magni(x, y); //asigno la magnitud a la parte real
			TDF_imagen[1](x, y) = 0.0; //hago cero la parte imaginaria por tanto hago cero la fase
		}
	//aplico la transofrmada inversa para obtener la imagen solo magnitud.
	//cimglist_apply(TDF_imagen, shift)(imagen.width()/2, imagen.height()/2, 0, 0,2);
	return TDF_imagen.get_FFT(true)[0];
}

template<class T>
CImg<T> get_imagen_solo_fase(CImg<T> imagen) {
	//devuelve la imagen con solo la fase (hace la magnitud 1)

	// OJO DEVUELVE SOLO LA PARTE CON VALORES REALES DE LA IMAGEN...

	//la parte real va a tener cos(fase) y la parte imaginaria (sen (fase))
	CImg<T> tita = get_fase<T> (imagen); // een tita tengo la fase de la imagen

	CImgList<T> tdf = imagen.get_FFT(); //obtengo la fft

	//recordar que si magnitud es 1-> 1*e^jtita=cos(tita)+j*sen (tita)
	cimg_forXY(tdf[0],x,y)
		{
			tdf[0](x, y) = cos(tita(x, y)); //parte real=1*cos tita
			tdf[1](x, y) = sin(tita(x, y)); // parte imaginaria sen(tita)
		}
	return tdf.get_FFT(true)[0]; //retorno solo la parte real
}

//////////////////////////////////////////////////////////////////////////////////
//Funciones mauro:
//////////////////////////////////////////////////////////////////////////////////

template<class T>
CImg<T> calcular_magnitud_fft(const CImg<T> &imagen, bool shift = true,
		bool log = true, bool normalize = true) {
	/* Devuelve la magntiud de la transformada de fourier de una imagen
	 * @param: imagen es la iamgen en el dominio espacial
	 * @shift (true por defecto) implica que es devuelta centrada
	 * @log (true por defecto): implica que se aplica logaritmo
	 * @normalize(true por defecto): implica normalizacion 0-1
	 * */
	CImgList<T> fft = imagen.get_FFT();
	CImg<T> magnitud = (fft[0].get_sqr() + fft[1].get_sqr()).sqrt();

	if (shift)
		magnitud.shift((int) floor(imagen.width() / 2), (int) floor(
				imagen.height() / 2), 0, 0, 2);

	if (log)
		magnitud.log();

	if (normalize)
		magnitud.normalize(0, 1);

	return magnitud;
}

template<class T>
CImgList<T> realimag2magfase(const CImgList<T> &realimag) {
	/* Dada una Lista con la parte real y imaginaria de la transf. de fourier
	 * calcula la magnitud y la fase de la transformadaq y las devuelve en un alista
	 * @real_imag: lista con parte real e imaginaria sobre la cual se saca la fase y magnitud
	 */
	CImg<T> magnitud = (realimag[0].get_sqr() + realimag[1].get_sqr()).sqrt();
	CImg<T> fase = realimag[1].get_atan2(realimag[0] + 0.01);
	return CImgList<T> (magnitud, fase);;
}

template<class T>
CImgList<T> magfase2realimag(const CImgList<T> &magfase) {

	/** Dada una lista compuesta por magnitud y fase genera una imagen compuesta por dicha magnitud y fase.
	 * @magfase es la lista con el primer elemento corresp. a la magnitud y el segundo a la fase
	 */
	CImg<T> real = magfase[1].get_cos().mul(magfase[0]);
	CImg<T> imag = magfase[1].get_sin().mul(magfase[0]);
	return CImgList<T> (real, imag);;
}
