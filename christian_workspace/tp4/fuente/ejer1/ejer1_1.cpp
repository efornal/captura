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
	CImg<unsigned char> irgb_0, irgb_1, irgb_2, imagen_rgb;
	CImg<unsigned char> ihsi_h, ihsi_s, ihsi_i, imagen_hsi;

	imagen_rgb.load("../../imagenes/patron.tif");

	CImgDisplay disp1, disp2;
	irgb_0.channel(0) = imagen_rgb.get_channel(0); //rojo
	irgb_1.channel(1) = imagen_rgb.get_channel(1); //azul
	irgb_2.channel(2) = imagen_rgb.get_channel(2); //verde

	CImgList<unsigned char> lista(imagen_rgb, irgb_0.channel(0), irgb_1, irgb_2);
	lista.display(disp1);
	disp1.set_title("rgb");
	imagen_hsi = imagen_rgb.get_RGBtoHSI();
	/*ihsi_h = imagen_hsi.get_channel(0); //obtengo canal h
	ihsi_s = imagen_hsi.get_channel(1); //obtengo canal s
	ihsi_i = imagen_hsi.get_channel(2); //obtengo canal i

	CImgList<float> lista1(imagen_hsi, ihsi_h, ihsi_i, ihsi_s);
	lista1.display(disp2);
	disp2.set_title("hsi");*/
	while (!disp1.is_closed()){}
	return 0;
}
