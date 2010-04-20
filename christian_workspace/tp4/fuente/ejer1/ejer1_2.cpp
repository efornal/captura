/*
 * ejer1_2.cpp
 *
 *  Created on: 15/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> imagen_rgb;
	CImg<double> imagen_hsi;

	imagen_rgb.load("../../imagenes/patron.tif");

	CImgDisplay disp1, disp2, disp3;

	imagen_hsi = imagen_rgb.get_RGBtoHSI();
	CImg<double> ihsi_h(imagen_rgb.width(), imagen_rgb.height(), 1, 3, 0);
	CImg<double> ihsi_s(imagen_rgb.width(), imagen_rgb.height(), 1, 3, 0);
	CImg<double> ihsi_i(imagen_rgb.width(), imagen_rgb.height(), 1, 3, 0);

	cimg_forXY(imagen_hsi, x,y)
		{
			/*POSTA: el H va entre 0 y 360 y S e I van de 0 a 1 com ola lista normaliza si
			 * no hago lo que hice abajo se ve el s y el i como _todo negro.... por eso hago
			 * eso aca abajo
			 * */
			ihsi_h(x, y, 0, 0) = (imagen_hsi(x, y, 0, 0) / 360) * 255;
			ihsi_s(x, y, 0, 1) = imagen_hsi(x, y, 0, 1) * 255;
			ihsi_i(x, y, 0, 2) = imagen_hsi(x, y, 0, 2) * 255;
		}

	CImgList<double> lista1(imagen_hsi, ihsi_h, ihsi_s, ihsi_i);
	disp1.set_title("hsi");
	lista1.display(disp1, 'y', 'c');


	disp2.set_title("imagen original");
	imagen_rgb.display(disp2);

	disp3.set_title("imagen invertida");
	invertir_HSI <double> (imagen_hsi).get_HSItoRGB().display(disp3);

	while (!disp2.is_closed()) {
	}
	return 0;
}
