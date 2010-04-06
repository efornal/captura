/*
 * ejer6_1.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/operadores_logicos.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> img;
	img.load("../../imagenes/letras1.tif");
	//8 bits image = 2^8=256 colores 0 a 255....
	/**
	 Con la imagen en escala de grises se aprecia como interpreta los bits:
	 dec  | bin
	 0    | 0000 0000
	 1    | 0000 0001
	 2    | 0000 0010
	 4    | 0000 0100
	 8    | 0000 1000
	 16   | 0001 0000
	 32   | 0010 0000
	 64   | 0100 0000

	 127  | 0111 1111 -> hasta aqui el bit 7 =0
	 ----------------
	 128  | 1000 0010 -> a partir de aqui el bit 7=1
	 ...  | 1@@@ @@@@
	 255  | 1111 1111
	 ________________
	 pos  : 7654 3210

	 para la posicion 7 (bit7) - ver en tabla a lo vertical
	 de 0-127 son todos ceros
	 de 128-255 son todos unos
	 por tanto la imagen correspondiente a este plano es una
	 mitad blanca mitad negra. y asi con el resto.
	 */

	CImgDisplay disp1, disp2;
	img.display(disp1);
	disp1.set_title("imagen original");

	CImg<unsigned char> aux(255, 255, 1, 1);

	CImgList<unsigned char> lista(AND(img, aux.fill(2)).normalize(0, 255), AND(
			img, aux.fill(4)).normalize(0, 255),
			AND(img, aux.fill(8)).normalize(0, 255), AND(img, aux.fill(16)),
			AND(img, aux.fill(32)), AND(img, aux.fill(64)), AND(img, aux.fill(
					128)));
	lista.display();

	return 0;
}
