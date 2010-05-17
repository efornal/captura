/*
 * ejer7_1.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib2/lut.h"

using namespace std;
using namespace cimg_library;

struct punto {
	int x;
	int y;
};

int main(int argc, char **argv) {
	CImg<unsigned char> imagen;
	float factor = 0;
	imagen.load("../../imagenes/earth.bmp");
	// si se ejecuta el ejercicio ejer1/ejer1_2_a.cpp... la imagen aparece en las coordenadas 447, 270 aprox.
	CImgDisplay disp1, disp2;
	imagen.display(disp1);
	disp1.set_title("imagen original");

	punto primero;
	punto segundo;
	primero.x = 447;
	primero.y = 0; // guarda esto medio que no se entiende pero es simplemente porque esta cambiado los ejes recordar que el
	//eje y empieza en la esquina superior izquierda y aumenta hacia abajo de la pantalla....
	segundo.x = imagen.width();
	segundo.y = 270;
	CImg<unsigned char> im_mod = lut_tramos2dimensiones<CImg<unsigned char> > (
			imagen, primero.x, primero.y, segundo.x, segundo.y, true, factor);
	im_mod.display(disp2);
	disp2.set_title("imagen modificada variando el factor - presiones las teclas hacia arriba y abajo para variarlo...");

	while (!disp2.is_closed()) {
		if (disp2.is_keyARROWUP()) {
			factor = clipp<float> (++factor);
		} else if (disp2.is_keyARROWDOWN()) {
			factor = clipp<float> (--factor);
		}
		im_mod = lut_tramos2dimensiones(imagen, primero.x, primero.y,
				segundo.x, segundo.y, true, factor);
		cout << "factor: " << factor << endl;
		im_mod.display(disp2);
	}
	return 0;
}
