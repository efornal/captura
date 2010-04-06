/*
 * ejer5_2.cpp
 *
 *  Created on: 05/04/2010
 *      Author: christian
 *      LAS OPERACIONES LOGICAS SE APLICAN SOBRE IMAGENES BINARIAS Y DEVUELVEN IMAGENES BINARIAS
 *      FIXME: funcionan igual como ya conociamos..? conclusion aparte?
 */
#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/operadores_logicos.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> img1(500, 500, 1, 1);
	CImg<unsigned char> img2(500, 500, 1, 1);
	const char blanco[] = { 255, 255, 255 };
	img1.draw_circle(500 / 2, 500 / 2, 100, blanco, 1);
	img2.draw_rectangle(100, 100, 300, 300, blanco, 1);
	CImgDisplay disp1, disp2;
	img1.display(disp1);
	disp1.set_title("Imagen 1");

	img2.display(disp2);
	disp2.set_title("Imagen 2");

	//by chaco:
	NOT(img2).display("NOT de cuadrado");
	AND(img1, img2).display("circulo AND cuadrado");
	AND(img2, img1).display("cuadrado AND circulo");
	OR(img1, img2).display("circulo OR cuadrado");
	OR(img2, img1).display("cuadrado OR circulo");
	XOR(img1, img2).display("circulo XOR cuadrado");
	XOR(img2, img1).display("cuadrado XOR circulo");
	NOTAND(img1, img2).display("circulo NOTAND cuadrado");
	NOTAND(img2, img1).display("cuadrado NOTAND circulo");

	while (!disp1.is_closed() && !disp2.is_closed()) {
	}

	return 0;
}
