/*
 * ejer4_1.cpp
 *
 *  Created on: 01/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/* Filtro emboss: relieve tipo repujado sobre una placa metalica, logra el realce de boredes
	 * para lograrlo
	 * sumar a la imagen su negativo desplazado
	 * (desplazar el negativo unos pixeles en alguna direccion obtenemos el efecto)
	 * segun se negativize una u otra imagen obtenemos efecto de relieve exterior o interior
	 * */

	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/letras1.tif");

	CImgDisplay disp1, disp2;

	/*FIXME: cuadno dice segun que imagen se negativize el ejecto sera relieve interior o exterior...
	 * en cual es exterior y en cual interior... se refiere a las dos lienas que puse aca abajo?*/
	emboss(imagen, 1, 1, false).display(disp1);
	emboss(negativo(imagen), 1, 1, false).display(disp2);
	while (!disp1.is_closed()) {
	}

	return 0;
}
