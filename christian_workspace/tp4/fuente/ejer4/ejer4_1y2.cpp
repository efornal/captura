/*
 * ejer4_1y2.cpp
 *
 *  Created on: 21/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> rio("../../imagenes/rio.jpg");
	CImgDisplay disp1(rio, "imagen del rio", 1), disp2, disp3;
	rio.get_histogram(255).display_graph(disp2, 3);
	//el color del rio esta entre 0 y 1 inclusive.
	CImg<float> rio_color(rio.width(), rio.height(), rio.depth(), 3); // rgb channels
	//cout<<rio.spectrum();
	cimg_forXY(rio, X, Y)
		{
			if (rio(X, Y) <= 1.0) {
				rio_color(X, Y, 1, 0) = 255.0; //rojo
				rio_color(X, Y, 1, 1) = 255.0; //verde
				rio_color(X, Y, 1, 2) = 0.0;
				//rojo+verde=amarillo
			} else {//dejo las cosas con el valor que estaban
				rio_color(X, Y, 1, 0) = rio.get_channel(0)(X, Y);
				rio_color(X, Y, 1, 1) = rio.get_channel(1)(X, Y);
				rio_color(X, Y, 1, 2) = rio.get_channel(2)(X, Y);
			}
		}
	rio_color.normalize(0, 255).display(disp3);
	while (!disp1.is_closed()) {
	}

	return 0;
}
