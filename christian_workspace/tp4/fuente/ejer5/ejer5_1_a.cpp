/*
 * ejer5_1.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen_oscura("../../imagenes/chairs_oscura.jpg"),
			imagen_oscura_R, imagen_oscura_G, imagen_oscura_B;
	imagen_oscura.resize(400,400);
	imagen_oscura_R = imagen_oscura.get_channel(0); //canal R
	imagen_oscura_G = imagen_oscura.get_channel(1); //canal G
	imagen_oscura_B = imagen_oscura.get_channel(2); //canal B
	CImgDisplay disp1(imagen_oscura, "imagen oscura", 1);
	CImgDisplay disp2(imagen_oscura_R, "canal r", 1);
	CImgDisplay disp3(imagen_oscura_G, "canal g", 1);
	CImgDisplay disp4(imagen_oscura_B, "canal b", 1);
	while (!disp1.is_closed()) {
	};
	return 0;
}
