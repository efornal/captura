/*
 * ejer5_1.cpp
 *
 *  Created on: 02/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> im1, im2;
	im1.load("../../imagenes/letras1.tif");
	im2.load("../../imagenes/letras2.tif");
	CImg<unsigned char> gris = grises();

	//convertir imagenes a binarias:
	CImg<unsigned char> im1_bin, im2_bin, im3_bin;
	im1_bin = get_binary(im1).normalize(0, 255);
	im2_bin = get_binary(im2).normalize(0, 255);
	im3_bin = get_binary(gris).normalize(0, 255);
	//FIXME: si no normalizo, no me muestra nada!! porque?

	CImgList<unsigned char> lista_imagenes(im1, im2, gris, im1_bin, im2_bin,
			im3_bin);
	lista_imagenes.display("Originales y sus Imagenes binarias");

	unsigned char blanco[] = { 255, 255, 255 };

	CImg<unsigned char> mapeo(256, 256, 1, 1);
	mapeo.fill(0);//borro fondo
	CImgList<unsigned char> lista1(gris,
			gris.get_threshold(0).normalize(0, 255), mapeo.draw_graph(
					gris.get_threshold(0).normalize(0, 255), blanco, 1, 1, 1));
	lista1.display(
			"Tonos grises 0 a 255 -- threshold en 0 -- grafica del threshold");

	mapeo.fill(0);//borro fondo
	CImgList<unsigned char> lista2(gris, gris.get_threshold(128).normalize(0,
			255), mapeo.draw_graph(gris.get_threshold(128).normalize(0, 255),
			blanco, 1, 1, 1));
	lista2.display(
			"Tonos grises 0 a 255 -- threshold en 128 -- grafica del threshold");

	mapeo.fill(0); //borro fondo

	CImgList<unsigned char> lista3(gris, gris.get_threshold(255).normalize(0,
			255), mapeo.draw_graph(gris.get_threshold(255).normalize(0, 255),
			blanco, 1, 1, 1));
	lista3.display(
			"Tonos grises 0 a 255 -- threshold en 255 -- grafica del threshold");
	return 0;
}
