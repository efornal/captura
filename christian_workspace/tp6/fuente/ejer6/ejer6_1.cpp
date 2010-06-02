/*
 * ejer6_1.cpp
 *
 *  Created on: 13/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include "../lib6/restauracion.h"

#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/parrot.tif", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original

	CImg<double> img_noise =
			img.normalize(0, 1).get_noise(5, 2).normalize(0, 1); // ruido impulsivo
	CImg<double> restaurada(img_noise);
	restaurada.normalize(0, 1);
	for (int i = 0; i < 5; i++) {
		restaurada = dist_acumulada(restaurada);
		cout << endl << "------- Errores -------------------------------"
				<< endl;
		cout << "Original-Ruido: " << img.MSE(img_noise) << endl;
		cout << "Original-Restaurada: " << img.MSE(restaurada) << endl;
	}
	(img, img_noise, restaurada).display("img - img noise - restaurada");

	return 0;
}
