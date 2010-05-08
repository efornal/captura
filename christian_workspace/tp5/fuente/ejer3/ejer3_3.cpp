/*
 * ejer3_3.cpp
 *
 *  Created on: 05/05/2010
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
#include "../lib5/figuras.h"
//#include "../../../tp4/fuente/lib4/CPDSI_functions.h"
#include "../../../tp3/fuente/lib3/mask.h"
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
	int frec_corte = 50;
	int orden = 1;
	CImg<float> H(img.width(), img.height(), 1, 1);

	CImgDisplay disp1, disp2;
	CImg<float> filtrada = aplicar_Butter_PB<float> (img, H, frec_corte, orden);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada");
	H.display(disp2);
	disp2.set_title("Filtro que se aplica");
	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWRIGHT()) {
			frec_corte+=2;
		} else if (disp1.is_keyARROWLEFT()) {
			frec_corte-=2;
		} else if (disp1.is_keyARROWUP()) {
			orden++;
		} else if (disp1.is_keyARROWDOWN()) {
			orden--;
		}
		filtrada = aplicar_Butter_PB<float> (img, H, frec_corte, orden);
		filtrada.display(disp1);
		disp1.set_title("imagen filtrada");

		H.display(disp2);
		disp2.set_title("Filtro que se aplica");
		cout << "Frec. corte: " << frec_corte << "     Orden: " << orden
				<< endl;
	}
	return 0;
}
