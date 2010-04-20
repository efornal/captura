/*
 * ejer4_1.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<double> imagen("../../imagenes/tablero.png");
	CImgDisplay disp1, disp2, disp3;
	generar_mascara_gaussiana<double> (9,9,1).display();

	imagen.display(disp1);
	disp1.set_title("original");

	imagen.get_convolve(generar_mascara3x3_todos1_promediadora<double> ()).display(disp2);
	disp2.set_title("original aplicando mascara de promediado");
	/* Al aumentar el tamanio de la mascara gaussiana con la misma varianza la imagen se hace notoramiente mas
	 * Disfuminada...
	 * FIXME: Al aume*ntar el tamanio lo que estaria haciendo es estirarla y por tanto la varianza seria mayor?
	 * si para la gaussiana usamos 3x3 la forma es /\ y no tienen mucha forma de gausseana
	 * (mas bien parece la promedio)... si aumentamos el tamaño toma mas forma de gaussiana: \/\/
	 */
	imagen.get_convolve(generar_mascara_gaussiana<double> (9,9,5)).display(disp3);
	disp3.set_title("original con mascara de tipo gaussiana");

	while (!disp3.is_closed()) {
	}
	return 0;
}
