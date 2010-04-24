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

int main(int argc, char **argv) {

	/*	no recuerdo si les comente, pero por las dudas, la función que deben usar para contaminar la imagen con
	 * ruido gaussiano es Imagen.get_noise(param1, param2);
	 * 	en los parámetros se especifica el tipo de ruido (gaussiano es el default) y la varianza.
	 * La media del ruido generado es cero. El ruido generado es aditivo.*/

	/*POSTA:
	 * para ver si la media del ruido es cero lo que tenes que hacer es sacar el
	 * brillo medio de la imagen ( promedio de todos los pixels ) y desp le agregas
	 * ruido haces de nuevo el proceso y te fijas si no cambia la media el ruido tiene
	 * media cero
	 * */

	CImg<double> imagen_limpia;
	imagen_limpia.load("../../imagenes/tablero.png");
	double varianza = 0.05;
	CImgDisplay disp1, disp2, disp3;
	imagen_limpia.display(disp1);
	cout<<"Media de la imagen original: "<<imagen_limpia.mean()<<endl;
	disp1.set_title("imagen original");

	/* Add noise to the image.
	 Parameters:
	 sigma 	= power of the noise. if sigma<0, it corresponds to the percentage of the maximum image value.
	 ntype 	= noise type. can be 0=gaussian, 1=uniform or 2=Salt and Pepper.
	 Returns:
	 A noisy version of the instance image.
	 */

	int cantidad_cuadros = 60;
	CImg<double> imagen_sucia[cantidad_cuadros];
	for (int i = 0; i < cantidad_cuadros; i++) {
		imagen_sucia[i] = imagen_limpia.get_noise(varianza);
	}
	cout<<endl<<"ruido"<<endl;
	imagen_limpia.get_noise(0.05).print();
	cout<<endl;
	imagen_sucia[10].display(disp3);
	imagen_sucia[10].print();
	cout<<"Media de la imagen con ruido: "<<imagen_sucia[10].mean()<<endl;

	disp3.set_title("imagen sucia 10");
	CImg<double> reconstruida = imagen_sucia[0];
	for (int i = 1; i < cantidad_cuadros; i++) {
		reconstruida = sumar<CImg<double> > (reconstruida, imagen_sucia[i], false); //false para que no divida por 2
	}
	reconstruida.display(disp2);
	disp2.set_title("reconstruida con 60 cuadros");
	while (!disp2.is_closed()) {
	}
	return 0;
}
