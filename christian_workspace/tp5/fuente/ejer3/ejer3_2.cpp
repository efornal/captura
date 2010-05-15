/*
 * ejer3_2.cpp
 *
 *  Created on: 08/05/2010
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
	CImg<unsigned char> img(filename); //imagen original
	img.normalize(0, 255);
	CImgDisplay disporiginal(img, "imagen original");
	int radio = 150;
	CImg<float> H(img.width(), img.height(), 1, 1);
	//circulo de altura 1 sobre una matriz de ceros:
	circulo_centrado(H.width() / 2, H.height() / 2, H, radio, 0);
	CImgDisplay disp1, disp2;

	CImg<float> filtrada = aplicar_PB_ideal<float> (img, radio);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada con filtro ideal");
	H.display(disp2);
	disp2.set_title("H(u,v) es es filtro que se aplica - esto es frec");
	while (!disp2.is_closed()) {
		disp2.wait();
		circulo_centrado(H.width() / 2, H.height() / 2, H, radio
				+ disp2.wheel(), 0); //vario radio.
		filtrada = aplicar_PB_ideal<float> (img, radio + disp2.wheel());
		filtrada.display(disp1);
		disp1.set_title("imagen filtrada con filtro ideal");

		H.display(disp2);
		disp2.set_title("H(u,v) es es filtro que se aplica - esto es frec");

		cout << "Frec. corte filtro ideal: " << radio+disp2.wheel() << endl;
	}
	return 0;
}
