/*
 * parcial2010.cpp
 *
 *  Created on: 03/06/2010
 *      Author: Christian Pfarher
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../../tp7/fuente/lib7/CPDSI_segmentacion.h"
#include "../../tp7/fuente/lib7/segmentacion.h"
#include "../../tp2/fuente/lib2/operadores_logicos.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/letras1.tif",
			"ruta archivo imagen");
	CImg<double> imagen(filename); //cargo la imagen
	CImgDisplay disp(imagen, "imagen");

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
