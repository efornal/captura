/*
 * ejer2_1.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h";

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> imagen("../../imagenes/tablero.png");
	CImg<unsigned char> resultado=imagen.convolve(mascara3x3 <unsigned char> ());

	CImgDisplay disp1, disp2, disp3;

	imagen.display(disp1); disp1.set_title("imagen original");
	resultado.display(disp2); disp2.set_title("imagen convolucionada con la mascara");
	mascara3x3 <unsigned char> ().display(disp3);
	disp3.set_title("mascara");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
