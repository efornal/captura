/*
 * ejer3_2.cpp
 *
 *  Created on: 21/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/huang.jpg");
	CImgDisplay disp1, disp2, disp3;
	imagen.normalize(0, 255.0);
	CImg<float> coloreada(imagen.width(), imagen.height(), 1, 3, 0);
	cimg_forXY(imagen, x, y)
		{
			if (imagen(x, y) > 128.0) {
				coloreada(x, y, 1, 0) = 0.0;//red
				coloreada(x, y, 1, 1) = 0.0;//green
				coloreada(x, y, 1, 2) = 255.0;//blue
			} else {
				coloreada(x, y, 1, 0) = 255.0;//red
				coloreada(x, y, 1, 1) = 0.0;//green
				coloreada(x, y, 1, 2) = 0.0;//blue
			}
		}

	imagen.display(disp1);
	disp1.set_title("imagen original");

	imagen.threshold(128).display(disp2); // ya esta normalizada
	disp2.set_title("imagen binaria");
	/*FIXME: para que ande hay que comentar las dos lineas que estan aqui debajo... porque!!?*/
	coloreada.display();
	 coloreada.display(disp3);
	 disp3.set_title("imagen coloreada");

	while (!disp1.is_closed() && !disp3.is_closed()) {
		disp3.wait();
	}

	return 0;
}
