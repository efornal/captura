/*
 * ejer4_2.cpp
 *
 *  Created on: 11/05/2010
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
#include "../lib5/lib5.h"
//#include "../lib5/figuras.h"
//#include "../../../tp4/fuente/lib4/CPDSI_functions.h"
//#include "../../../tp3/fuente/lib3/mask.h"
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<unsigned char> img(filename); //imagen original
	img.normalize(0, 255);
	CImgDisplay disporiginal(img, "imagen original");
	int radio = 150;
	CImg<float> H(img.width(), img.height(), 1, 1);
	//circulo de altura 1 sobre una matriz de ceros:
	circulo_centrado(H.width() / 2, H.height() / 2, H, radio, 0);
	CImgDisplay disp1, disp2;

	CImg<float> filtrada = aplicar_PA_ideal<float> (img, radio);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada con PA ideal");
	H.display(disp2);
	disp2.set_title("Filtro que se aplica PA ideal");
	while (!disp2.is_closed()) {
		disp2.wait();
		circulo_centrado_inverso(H.width() / 2, H.height() / 2, H, radio
				+ disp2.wheel(), 0); //vario radio.
		filtrada = aplicar_PA_ideal<float> (img, radio + disp2.wheel());
		filtrada.display(disp1);
		disp1.set_title("imagen filtrada con PA ideal");

		H.display(disp2);
		disp2.set_title("Filtro que se aplica PA ideal");

		cout << "Frec. corte filtro ideal: " << radio+disp2.wheel() << endl;
	}
	return 0;
}
