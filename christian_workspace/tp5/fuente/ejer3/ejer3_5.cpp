/*
 * ejer3_5.cpp
 *
 *  Created on: 09/05/2010
 *      Author: christian
 */
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	img.normalize(0, 255);
	CImgDisplay disporiginal(img, "imagen original");

	float varianza = 1.0;

	CImg<double> H(img.width(), img.height(), 1, 1);
	CImgDisplay disp1, disp2;
	CImg<double> filtrada = aplicar_PB_Gaussiano<double> (img, H, varianza);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada con filtro gaussiano en frecuencia");
	H.display(disp2);
	disp2.set_title("Filtro Gaussiano aplicado");
	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWUP()) {
			varianza++;
		} else if (disp1.is_keyARROWDOWN()) {
			varianza--;
		}
		filtrada = aplicar_PB_Gaussiano<double> (img, H, varianza);

		filtrada.display(disp1);
		disp1.set_title("imagen filtrada con filtro gaussiano en frecuencia");

		H.display(disp2);
		disp2.set_title("Filtro Gaussiano aplicado");
		cout << "Varianza: " << varianza << endl;
	}
	return 0;
}
