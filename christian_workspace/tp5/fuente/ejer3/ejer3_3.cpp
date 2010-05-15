/*
 * ejer3_3.cpp
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
	float frec_corte = 50.0;
	float orden = 1.0;
	CImg<double> H(img.width(), img.height(), 1, 1);

	CImgDisplay disp1, disp2;
	CImg<double> filtrada = aplicar_Butter_PB<double> (img, H, frec_corte, orden);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada");
	H.display(disp2);
	disp2.set_title("Filtro que se aplica");
	while (!disp1.is_closed()) {
		if (disp1.is_keyARROWRIGHT()) {
			frec_corte+=1;
		} else if (disp1.is_keyARROWLEFT()) {
			frec_corte-=1;
		} else if (disp1.is_keyARROWUP()) {
			orden+=0.5;
		} else if (disp1.is_keyARROWDOWN()) {
			orden-=0.5;
		}
		filtrada = aplicar_Butter_PB<double> (img, H, frec_corte, orden);
		filtrada.display(disp1);
		disp1.set_title("imagen filtrada");

		H.display(disp2);
		disp2.set_title("Filtro Butter pasa bajos");
		cout << "Frec. corte: " << frec_corte << "     Orden: " << orden
				<< endl;
	}
	return 0;
}
