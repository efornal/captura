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
void linea_horizontal(CImg<T> &imagen, int coord_y, float angulo=0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_line(0, coord_y, imagen.height(), coord_y, blanco);
}

template<class T>
void linea_vertical(CImg<T> &imagen, int coord_x, float angulo=0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_line(coord_x, 0, coord_x, imagen.height(), blanco);
}

template<class T>
CImg<T> get_fase(CImg<T> imagen) {
	CImgList<T> tdf = imagen.get_FFT(); //obtengo la fft
	CImg<T> real = tdf[0];
	CImg<T> imag = tdf[1];

	complex<T> I(0., 1.); //definicion de la constatnte imaginaria I=sqrt(-1)
	CImg<T> magnitud(imagen.width(), imagen.height(), 1, 1);
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
void cuadrado_centrado(CImg<T> &imagen, int dimx = 20, int dimy = 20, int x0 =
		0, int y0 = 0, float angulo=0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	int x1 = x0 + dimx;
	int y1 = y0 + dimy;
	imagen.draw_rectangle(x0, y0, x1, y1, blanco);
}

template<class T>
void circulo_centrado(int x0, int y0, CImg<T> &imagen, int radio = 20, float angulo=0) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.fill(0);
	imagen.draw_circle(x0, y0, abs(radio), blanco, 1);
	imagen.rotate(angulo);
}

