/*
 * ejer4_1.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/tablero.png");
	CImgDisplay disp1, disp2, disp3;
	generar_mascara_gaussiana<float> ().display();

	imagen.display(disp1);
	disp1.set_title("original");

	imagen.get_convolve(generar_mascara3x3_todos1_promediadora<float> ()).display(disp2);
	disp2.set_title("original aplicando mascara de promediado");

	imagen.get_convolve(generar_mascara_gaussiana<float> ()).display(disp3);
	disp3.set_title("original con mascara de tipo gaussiana");

	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
