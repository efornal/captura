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
CImg<T> get_magnitud(CImg<T> imagen) {
	CImgList<T> tdf = imagen.get_FFT(); //obtengo la fft
	CImg<T> real = tdf[0];
	CImg<T> imag = tdf[1];

	complex<T> I(0., 1.); //definicion de la constatnte imaginaria I=sqrt(-1)
	CImg<T> magnitud(imagen.width(), imagen.height(), 1, 1);

	for (int i = 0; i < imagen.width(); i++) {
		for (int j = 0; j < imagen.height(); j++) {
			magnitud(i, j) = sqrt(pow(real(i, j), 2) + pow(imag(i, j), 2));
		}
	}
	return magnitud;
}

template<class T>
CImg<T> get_imagen_solo_magnitud(CImg<T> imagen) {
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

