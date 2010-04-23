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
#include <iostream>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

template<class T>
void linea_horizontal(CImg<T> &imagen, int coord_y) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.draw_line(0, coord_y, imagen.height(), coord_y,
			blanco);
}

template<class T>
void linea_vertical(CImg<T> &imagen, int coord_x) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	imagen.draw_line(coord_x, 0, coord_x, imagen.height(),
			blanco);
}

template<class T>
void cuadrado_centrado(CImg<T> &imagen, int dimx, int dimy) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	int x0 = ((imagen.width())/2) - (int) (dimx / 2);
	int y0 = (imagen.height()/2) - (int) (dimy / 2);
	int x1 = (imagen.width()/2) + (int) (dimx / 2);
	int y1 = (imagen.height()/2) + (int) (dimy / 2);
	imagen.draw_rectangle(x0, y0, x1, y1, blanco);
}

template<class T>
void circulo_centrado(CImg<T> &imagen, int radio = 20) {
	unsigned char blanco[] = { 255, 255, 255 }; //Define color blanco
	int x1=(int) imagen.width()/2;
	int y1=(int) imagen.height()/2;
	imagen.draw_circle(x1, y1, abs(radio), blanco, 1);
}

