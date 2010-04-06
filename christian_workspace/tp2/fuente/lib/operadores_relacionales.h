/*
 * operadores_relacionales.h
 *
 *  Created on: 06/04/2010
 *      Author: esteban
 */
#include <CImg.h>

using namespace cimg_library;
//FIXME: quien define ese valor de 0 y 255... ? porque no puede ser al reves?
CImg<unsigned char> menor(CImg<unsigned char> img1, CImg<unsigned char> img2) {
	/* si el valor de la imagen 1 es menor que el valor de la imagen 2, asigna 0 (negro)
	 * sino asigna 255 (blanco)
	 * */
	cimg_forXY( img1, x, y )
		{
			img1(x, y) = (img1(x, y) < img2(x, y)) ? 0 : 255;
		}
	return img1;
}

CImg<unsigned char> menor_igual(CImg<unsigned char> img1,
		CImg<unsigned char> img2) {
	cimg_forXY( img1, x, y )
		{
			img1(x, y) = (img1(x, y) <= img2(x, y)) ? 0 : 255;
		}
	return img1;
}

CImg<unsigned char> mayor(CImg<unsigned char> img1, CImg<unsigned char> img2) {
	cimg_forXY( img1, x, y )
		{
			img1(x, y) = (img1(x, y) > img2(x, y)) ? 0 : 255;
		}
	return img1;
}

CImg<unsigned char> mayor_igual(CImg<unsigned char> img1,
		CImg<unsigned char> img2) {
	cimg_forXY( img1, x, y )
		{
			img1(x, y) = (img1(x, y) >= img2(x, y)) ? 0 : 255;
		}
	return img1;
}
