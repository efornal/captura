/*
 * ejer1_3.cpp
 *
 *  Created on: 22/05/2010
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
#include "../lib7/segmentacion.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/bone.tif",
			"ruta archivo imagen");

	CImg<double> img(filename); //imagen original
	CImgDisplay disp(img, "imagen original");

	return 0;
}
