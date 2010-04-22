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
	/*FIXME: analizar el histograma
	 * no se como analizarlo... a que se debe esa forma tipo gaussiana?
	 * */
	CImg<float> rio("../../imagenes/rio.jpg"); //tiene valores entre 0 y 255
	CImgDisplay disp1(rio, "imagen del rio", 1), disp2, disp3;
	rio.get_histogram(255).display_graph(disp2, 3);
	int umbral = 20;
	CImg<float> rio_color(rio.width(), rio.height(), 1, 3); // rgb channels
	rio_color.display(disp3);
	disp3.set_title("identificacion del rio");
	while (!disp3.is_closed()) {
		disp3.wait();
		if (disp3.is_keyARROWUP())
			umbral++;
		else if (disp3.is_keyARROWDOWN())
			umbral--;

		cimg_forXY(rio, X, Y)
			{
				if (rio(X, Y) <= umbral) {
					rio_color(X, Y, 0, 0) = 255.0; //rojo
					rio_color(X, Y, 0, 1) = 255.0; //verde
					rio_color(X, Y, 0, 2) = 0.0;
					//rojo+verde=amarillo
				} else {//dejo las cosas con el valor que estaban
					rio_color(X, Y, 0, 0) = rio(X, Y, 0, 0);
					rio_color(X, Y, 0, 1) = rio(X, Y, 0, 0);
					rio_color(X, Y, 0, 2) = rio(X, Y, 0, 0);
				}
			}
		rio_color.display(disp3);
		disp3.set_title("identificacion del rio");
		cout<<"Umbral: "<<umbral<<endl;
	}
	return 0;
}
