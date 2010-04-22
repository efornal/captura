/*
 * ejemplo1.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib5.h"
#include "../lib/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> img_circ(256, 256, 1, 1, 0);
	CImg<unsigned char> img_lin1(256, 256, 1, 1, 0);
	CImg<unsigned char> img_lin2(256, 256, 1, 1, 0);
	CImg<unsigned char> img_cuad(256, 256, 1, 1, 0);

	circulo_centrado<unsigned char> (img_circ, 100);
	cuadrado_centrado<unsigned char> (img_cuad, 50, 50);
	linea_vertical<unsigned char> (img_lin1, 50);
	linea_horizontal<unsigned char> (img_lin2, 50);

	CImgDisplay disp1, disp2, disp3, disp4;
	img_circ.display(disp1);
	img_lin1.display(disp2);
	img_lin2.display(disp3);
	img_cuad.display(disp4);
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
