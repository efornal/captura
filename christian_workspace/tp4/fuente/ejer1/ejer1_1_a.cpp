/*
 * ejer1_1.cpp
 *
 *  Created on: 15/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> imagen_rgb;
	CImg<double> imagen_hsi;

	imagen_rgb.load("../../imagenes/patron.tif");

	CImgDisplay disp1, disp2;

	CImg<unsigned char> irgb_0(imagen_rgb);
	CImg<unsigned char> irgb_1(imagen_rgb);
	CImg<unsigned char> irgb_2(imagen_rgb);

	cimg_forXY(imagen_rgb, x,y)
		{
			irgb_0(x, y, 0, 0) = imagen_rgb(x, y, 0, 0);
			irgb_0(x, y, 0, 1) = 0;//pongo en cero el canal verde
			irgb_0(x, y, 0, 2) = 0; //pongo en cero el canal azul

			irgb_1(x, y, 0, 0) = 0;//pongo en cero el canal rojo
			irgb_1(x, y, 0, 1) = imagen_rgb(x, y, 0, 1);
			irgb_1(x, y, 0, 2) = 0;//pongo en cero el canal azul

			irgb_2(x, y, 0, 0) = 0; //pongo en cero el canal rojo
			irgb_2(x, y, 0, 1) = 0; //pongo en cero el canal verde
			irgb_2(x, y, 0, 2) = imagen_rgb(x, y, 0, 2);
		}
	//rojo+verde=amarillo
	//verde+azul=cian
	CImgList<unsigned char> lista(imagen_rgb, irgb_0, irgb_1, irgb_2);
	lista.display(disp1, 'y', 'c');
	disp1.set_title("imagen rgb y sus respectivos canales");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
