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
void linea_horizontal(CImg<T> &imagen, int coord_y, float angulo = 0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_line(0, coord_y, imagen.height(), coord_y, blanco);
	imagen.rotate(angulo, imagen.width() / 2, imagen.height() / 2, 1.0, 2, 1);
}

template<class T>
void linea_vertical(CImg<T> &imagen, int coord_x, float angulo = 0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_line(coord_x, 0, coord_x, imagen.height(), blanco);
	imagen.rotate(angulo, imagen.width() / 2, imagen.height() / 2, 1.0, 2, 1);
}

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
	//devuelve la imagen con solo la magnitud (o sea fase=0)
	// OJO DEVUELVE SOLO LA PARTE CON VALORES REALES DE LA IMAGEN...
	CImgList<> TDF_imagen = imagen.get_FFT(); //me devuelve la ifft

	cimg_forXY(TDF_imagen[1], x, y) //recorro las imaginarias
		{
			TDF_imagen[1](x, y) = 0.0; //hago cero la parte imaginaria por tanto hago cero la fase
		}
	//aplico la transofrmada inversa para obtener la imagen solo magnitud.
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
	cimg_forXY(tdf[0],x,y) {
		tdf[0](x,y)=cos (tita(x,y)); //parte real=1*cos tita
		tdf[1](x,y)=sin (tita(x,y)); // parte imaginaria sen(tita)
	}
	return tdf.get_FFT(true)[0]; //retorno solo la parte real
}
template<class T>
void cuadrado_centrado(CImg<T> &imagen, int dimx = 20, int dimy = 20, int x0 =
		0, int y0 = 0, float angulo = 0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	int x1 = x0 + dimx;
	int y1 = y0 + dimy;
	imagen.draw_rectangle(x0, y0, x1, y1, blanco);
	imagen.rotate(angulo, (int) (x1 - x0) / 2, (int) (y1 - y0) / 2, 1.0, 2, 1);
}

template<class T>
void circulo_centrado(int x0, int y0, CImg<T> &imagen, int radio = 20,
		float angulo = 0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_circle(x0, y0, abs(radio), blanco, 1);
	imagen.rotate(angulo, x0, y0, 1.0, 2, 1);
}

