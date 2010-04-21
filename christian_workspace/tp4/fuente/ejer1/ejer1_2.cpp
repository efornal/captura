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
	CImg<double> ihsi_h = imagen_hsi.get_channel(0);
	CImg<double> ihsi_s = imagen_hsi.get_channel(1);
	CImg<double> ihsi_i = imagen_hsi.get_channel(2);

	cimg_forXY(imagen_hsi, x,y)
		{
			/*POSTA: el H va entre 0 y 360 y S e I van de 0 a 1 com ola lista normaliza si
			 * no hago lo que hice abajo se ve el s y el i como _todo negro.... por eso hago
			 * eso aca abajo
			 *
			 * */
			ihsi_h(x, y) = (imagen_hsi(x, y, 0, 0) / 360) * 255;
			ihsi_s(x, y) = imagen_hsi(x, y, 0, 1) * 255;
			ihsi_i(x, y) = imagen_hsi(x, y, 0, 2) * 255;
		}

	CImgList<double> lista1(imagen_rgb, imagen_hsi, ihsi_h, ihsi_s, ihsi_i);
	disp1.set_title("hsi");
	lista1.display(disp1, 'y', 'c');

//FIXME: esto no funciona
	int H1;
	cimg_forXY(imagen_hsi, x,y)
		{
			int H = imagen_hsi(x, y, 0, 0);
			int S = imagen_hsi(x, y, 0, 1);
			int I = imagen_hsi(x, y, 0, 2);

			if (H >= 0 && H < 120) {
				H1 = 240 + H;
			} else if (H >= 120 && H < 240) {
				H1 = 240 - (H - 120);
			} else {//h esta entre 240 y 360}
				H1 = H - 360;
			}
			imagen_hsi(x, y, 0, 0) = (H1 / 360) * 255;
			imagen_hsi(x, y, 0, 1) = imagen_hsi(x, y, 0, 1) * 255;
			imagen_hsi(x, y, 0, 2) = imagen_hsi(x, y, 0, 2) * 255;
		}
	disp3.set_title("imagen invertida");
	imagen_hsi.get_HSItoRGB().display(disp3);

	while (!disp1.is_closed()) {
	}
	return 0;
}
