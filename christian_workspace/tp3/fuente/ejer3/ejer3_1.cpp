/*
 * ejer2_1.cpp
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

	CImg<float> resultado3 = imagen.get_convolve(generar_mascara<float> (3));
	CImg<float> resultado15 = imagen.get_convolve(generar_mascara<float> (15));
	CImg<float> resultado30 = imagen.get_convolve(generar_mascara<float> (30));
	CImg<float> resultado50 = imagen.get_convolve(generar_mascara<float> (50));
	/*POSTA: filtro de promedidado -  al aumentar el tamanio de la mascara promedias mas valores y por tanto
	 * vas haciendo cada vez menos notoria la diferencia entre pixeles vecinos y por
	 * lo tanto resulta en una imagen mas disfuminada */
	CImgDisplay disp1, disp2, disp3, disp4, disp5;

	imagen.display(disp1);
	disp1.set_title("imagen original");

	resultado3.display(disp2);
	disp2.set_title("imagen aplicando mascara de 3x3");

	resultado15.display(disp3);
	disp3.set_title("imagen aplicando mascara de 15x15");

	resultado30.display(disp4);
	disp4.set_title("imagen aplicando mascara de 30x30");

	resultado50.display(disp5);
	disp5.set_title("imagen aplicando mascara de 50x50");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
