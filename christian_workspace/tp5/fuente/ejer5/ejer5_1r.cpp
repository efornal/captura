/*
 * ejer5_1r.cpp
 *
 *  Created on: 15/05/2010
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
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/reunion.tif", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	CImgDisplay disp(img, "imagen");
	float frec_corte = 20.0;
	float gl = 0.0;
	float gh = 1.0;
	float orden = 1.0;
	CImg<double> filtrada = aplicar_filtrado_homomorfico<double> (img,
			get_homomorfico<double> (img, frec_corte, gl, gh, orden));
	CImgDisplay disp2(filtrada, "imagen filtrada");
	CImgDisplay disp3(get_homomorfico<double>(img, frec_corte, gl, gh, orden));

	while ((!disp.is_closed() && !disp.is_keyQ())) {
		//disp.wait();
		if (disp2.is_keyARROWUP()) {
			orden++;
		} else if (disp2.is_keyARROWDOWN()) {
			orden--;
		} else if (disp2.is_keyARROWRIGHT()) {
			frec_corte++;
		} else if (disp2.is_keyARROWLEFT()) {
			frec_corte--;
		} else if (disp2.is_keyH()) {
			gh+=0.05;
		} else if (disp2.is_keyY()) {
			gh-=0.05;
		} else if (disp2.is_keyL()) {
			gl+=0.05;
		} else if (disp2.is_keyO()) {
			gl-=0.05;
		}
		filtrada = aplicar_filtrado_homomorfico<double> (img, get_homomorfico<
				double> (img, frec_corte, gl, gh, orden));
		filtrada.display(disp2);
		get_homomorfico<double>(img, frec_corte, gl, gh, orden).display(disp3);
		disp2.set_title("imagen filtrada - Usar: H, Y, L, O y flechas");
		cout << "Orden: " << orden << "  -  Frec Corte: " << frec_corte
				<< "  -  gl: " << gl << "  -  gh: " << gh << endl;
	}

	return 0;
}
