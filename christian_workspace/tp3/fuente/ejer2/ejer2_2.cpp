/*
 * ejer2_2.cpp
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

	CImg<float> resultado = imagen.get_correlate(mascara3x3<float> ());

	CImgDisplay disp1, disp2;
	imagen.display(disp1);
	disp1.set_title("imagen original");
	resultado.display(disp2);
	disp2.set_title("imagen correlacionada con la mascara");
	mascara3x3<float> ().normalize(0, 255).display("mascara");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
