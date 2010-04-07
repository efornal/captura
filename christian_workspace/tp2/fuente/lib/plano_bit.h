/*
 * plano_bit.h
 *
 *  Created on: 06/04/2010
 *      Author: chaco
 */
#define UNICODE
#include <CImg.h>

using namespace cimg_library;

/* Cuando hago lo de los planos de bits en realidad lo que estoy haciendo al ir corriendo el bit es
 * ir aplicando un umbral (1, 2, 4, 8, 16, 32, 64.... etc.) cuantizado en x niveles 2^x...
 * Obviamente que con los bits mas significativos por ejemplo 1000 0000 = 64 voy a tener mayor detalle que
 * si utilizo 01000 0000 =32 por tener menos niveles de cuantizacion y por tanto menos niveles de grises a representar.
 * */
CImg<unsigned char> plano_de_bit(CImg<unsigned char> img, int nro = 0) {

	if (nro > 0) {
		cimg_forXY(img,x,y)
			{
				img(x, y) = (img(x, y) >> nro) & 0x00000001;
				//cout<<img(x,y)<<endl; //FIXME: porque si pongo esto en consola no me lo muestra en binario?
			}
	} else {
		cimg_forXY(img,x,y)
			{
				img(x, y) = (img(x, y)) & 0x00000001;
			}
	}

	/* 0   ==  0000 0000     => 0 >> 1   =  0000 0000  ==  0
	   2   ==  0000 0010     => 2 >> 1   =  0000 0001  ==  1
	   & -> operador and bit a bit o bitand
	 * */
	return img;
}

int clipp_plano(int valor) {
	if (valor > 7)
		return 7;
	else if (valor < 0)
		return 0;
	else
		return valor;
}
