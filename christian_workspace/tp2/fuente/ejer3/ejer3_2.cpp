/*
 * ejer3_2.cpp
 *
 *  Created on: 07/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;
//TODO: hacerlo
int main(int argc, char **argv) {

	/*	no recuerdo si les comente, pero por las dudas, la función que deben usar para contaminar la imagen con
	 * ruido gaussiano es Imagen.get_noise(param1, param2);
	 * 	en los parámetros se especifica el tipo de ruido (gaussiano es el default) y la varianza.
	 * La media del ruido generado es cero. El ruido generado es aditivo.*/

	CImg<unsigned char> imagen_limpia;
	imagen_limpia.load("../../imagenes/hubble.tif");
	double varianza = 0.05;

	/* Add noise to the image.
	 Parameters:
	 sigma 	= power of the noise. if sigma<0, it corresponds to the percentage of the maximum image value.
	 ntype 	= noise type. can be 0=gaussian, 1=uniform or 2=Salt and Pepper.
	 Returns:
	 A noisy version of the instance image.

	 * */
	CImg <unsigned char> imagen_sucia=imagen_limpia.get_noise(varianza);
	imagen_sucia.display("ruidosa");
	return 0;
}
