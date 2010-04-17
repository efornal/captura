/*
 * ejer4_2.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/hubble.tif");
	CImgDisplay disp1, disp2, disp3;
	imagen.display(disp1);
	disp1.set_title("imagen original");

	CImg<float> resultado = imagen.get_convolve(generar_mascara<float> (7));
	resultado.display(disp2);
	disp2.set_title("imagen filtrada");

	resultado.quantize(2).display(disp3);
	disp3.set_title("imagen con objetos grandes");
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
