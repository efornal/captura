/*
 * ejer5_1_c.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen_oscura("../../imagenes/chairs_oscura.jpg"); //cargo la imagen

	imagen_oscura.resize(500, 500);
	int dx = imagen_oscura.width();
	int dy = imagen_oscura.height();

	CImg<float> imagen_oscura_HSI(dx, dy, 1, 3), imagen_oscura_HSI_H(dx, dy, 1,
			1), imagen_oscura_HSI_S(dx, dy, 1, 1), imagen_oscura_HSI_I(dx, dy,
			1, 1);
	imagen_oscura_HSI = imagen_oscura.get_RGBtoHSI(); //obtengo la imagen en HSI

	cimg_forXY(imagen_oscura_HSI, x, y) //obtengo componenes HSI de la imagen oscura
		{ //obtengo componenes HSI
			imagen_oscura_HSI_H(x, y) = imagen_oscura_HSI(x, y, 0, 0);
			imagen_oscura_HSI_S(x, y) = imagen_oscura_HSI(x, y, 0, 1);
			imagen_oscura_HSI_I(x, y) = imagen_oscura_HSI(x, y, 0, 2);
		}
	visualizar_HSI <float> (imagen_oscura_HSI_H, imagen_oscura_HSI_S,
			imagen_oscura_HSI_I);
	CImgDisplay disp1(imagen_oscura_HSI_H, "canal H");
	CImgDisplay disp2(imagen_oscura_HSI_S, "canal S");
	CImgDisplay disp3(imagen_oscura_HSI_I, "canal I");
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
