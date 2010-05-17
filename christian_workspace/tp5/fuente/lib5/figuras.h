/*
 * figuras.h
 *
 *  Created on: 06/05/2010
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

template<class T>
void circulo_centrado_inverso(int x0, int y0, CImg<T> &imagen, int radio = 20,
		float angulo = 0) {
	unsigned char negro[] = { 0.0,0.0,0.0 }; //Define color blanco
	imagen.fill(255.0);
	imagen.draw_circle(x0, y0, abs(radio), negro, 1);
	imagen.rotate(angulo, x0, y0, 1.0, 2, 1);
}
