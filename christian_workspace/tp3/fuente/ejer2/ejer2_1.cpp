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

	CImg<float> resultado = imagen.get_convolve(generar_mascara3x3<float> ());

	CImgDisplay disp1, disp2;
	imagen.display(disp1);
	disp1.set_title("imagen original");
	resultado.display(disp2);
	disp2.set_title("imagen convolucionada con la mascara");
	generar_mascara3x3<float> ().normalize(0, 255).display("mascara");
	/* POSTA: cuando convoluciono la imagen y la mascara con todos los valores iguales
	 * la imagen queda difusa porque para cada pixel le estas asignando el promedio
	 * de los vecinos
	 * */
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
