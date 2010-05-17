/*
 * ejer1_2.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */
//a la hora de identificar la iamgen, la fase tiene mucho mas importancia
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
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option( "-f", "../../imagenes/avion.jpg",

	                                        "ruta archivo imagen" );
	CImg<unsigned char> img(filename); //imagen original

	//obtener imagen de solo magnitud considerando fase cero:
	CImg<double> imagen_solo_magnitud = get_imagen_solo_magnitud<double> (img); //fixme:esta funcion no anda bien... preguntar po rlo del centrado
	//obtener imagen de solo fase considerando magnitud1:
	CImg<double> imagen_solo_fase = get_imagen_solo_fase<double> (img);
	CImgDisplay disp0(img, "imagen original");
	CImgDisplay disp1(imagen_solo_magnitud.log().normalize(0,255), "imagen solo magnitud"); //normalizo para que se vea algo...
	CImgDisplay disp2(imagen_solo_fase, "image solo fase");
	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
