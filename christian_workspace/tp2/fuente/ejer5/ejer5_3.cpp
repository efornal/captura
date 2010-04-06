/*
 * ejer5_3.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/operadores_relacionales.h" //FIXME: ver si estan bien programadas las funciones...
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> im1, im2;
	im1.load("../../imagenes/letras1.tif");
	im2.load("../../imagenes/letras2.tif");

	/*LAS OPERACIONES RELACIONALES SE APLICAN A IMAGENES EN ESCALAS DE GRISES Y DAN COMO RESULTADOS IMAGENES BINARIAS
	 * */
	CImgList<unsigned char> lista1(im1, im2, menor(im1, im2), menor(im2, im1));
	lista1.display(
			"im1        -       im2                - menor (im1, im2)      - menor (im2, im1)");

	CImgList<unsigned char> lista2(im1, im2, menor_igual(im1, im2),
			menor_igual(im2, im1));
	lista2.display(
			"im1        -       im2                - menor_igual (im1, im2)      - menor_igual (im2, im1)");

	CImgList<unsigned char> lista3(im1, im2, mayor(im1, im2), mayor(im2, im1));
	lista3.display(
			"im1        -       im2                - mayor (im1, im2)      - mayor (im2, im1)");

	CImgList<unsigned char> lista4(im1, im2, mayor_igual(im1, im2), mayor_igual(im2, im1));
	lista4.display(
			"im1        -       im2                - mayor_igual (im1, im2)      - mayor_igual (im2, im1)");

	return 0;
}
