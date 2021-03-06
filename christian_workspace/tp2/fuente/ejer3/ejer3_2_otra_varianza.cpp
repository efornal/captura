/*
 * ejer3_2.cpp
 *
 *  Created on: 07/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib2/lut.h"
//#include "../lib2/op_aritmeticos.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	/*	no recuerdo si les comente, pero por las dudas, la función que deben usar para contaminar la imagen con
	 * ruido gaussiano es Imagen.get_noise(param1, param2);
	 * 	en los parámetros se especifica el tipo de ruido (gaussiano es el default) y la varianza.
	 * La media del ruido generado es cero. El ruido generado es aditivo.*/

	//le cambie la varianza
	CImg<double> imagen_limpia;
	imagen_limpia.load("../../imagenes/tablero.png");
	double varianza = 50;

	CImgDisplay disp1, disp2, disp3;
	imagen_limpia.display(disp1);
	disp1.set_title("imagen original");

	/* Add noise to the image.
	 Parameters:
	 sigma 	= power of the noise. if sigma<0, it corresponds to the percentage of the maximum image value.
	 ntype 	= noise type. can be 0=gaussian, 1=uniform or 2=Salt and Pepper.
	 Returns:
	 A noisy version of the instance image.
	 */
	int cantidad_cuadros = 100;
	CImg<double> imagen_sucia[cantidad_cuadros];
	for (int i = 0; i < cantidad_cuadros; i++) {
		imagen_sucia[i] = imagen_limpia.get_noise(varianza); //contamino la imagen con ruido
	}

	imagen_sucia[10].display(disp3); //muestro la imagen_sucia 10
	disp3.set_title("imagen sucia 10");

	CImg<double> reconstruida = imagen_sucia[0];
	for (int i = 1; i < cantidad_cuadros; i++) {
		reconstruida = sumar <double> (reconstruida, imagen_sucia[i],
				false); //pongo false para que no me ladivida por 2
	}
	cimg_forXY( reconstruida, x, y )
		{
			reconstruida(x, y) = (reconstruida(x, y) / (double) cantidad_cuadros);
		}
	reconstruida.display(disp2);
	disp2.set_title("reconstruida con 100 cuadros");
	while (!disp2.is_closed()) {
	}
	return 0;
}
