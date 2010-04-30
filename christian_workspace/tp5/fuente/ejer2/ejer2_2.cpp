/*
 * ejer1_2.cpp
 *
 *  Created on: 22/04/2010
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
#include "../lib/lib5.h"
#include "../../../tp4/fuente/lib/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<double> img("../../imagenes/avion.jpg"); //imagen original
	CImg<double> img_aeropuerto ("../../imagenes/aeropuerto.jpg");
	CImgList <double> lista_imagenes(img, img_aeropuerto);
	CImgDisplay displis1(lista_imagenes);
	displis1.set_title("Imagenes originales");
//TODO: hacerlo...

	while (!displis1.is_closed()) {
		displis1.wait();
	}
	return 0;
}
