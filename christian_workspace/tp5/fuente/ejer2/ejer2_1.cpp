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
	CImgDisplay disp1(imagen_solo_magnitud.log(), "imagen solo magnitud"); //normalizo para que se vea algo...
	CImgDisplay disp2(imagen_solo_fase, "image solo fase");
	////////////////////////////////////////////////////////////////////////////////

	CImgList<double> IMG = img.get_FFT(); //obtengo la transf de fourier;
	CImgList<double> real_imag = realimag2magfase(IMG);

	CImg<double> vacio(img.width(), img.height(), 1, 1, 0);
	//imagen solo magnitud:
	CImg<double> img_solo_mag = magfase2realimag( CImgList<double> (IMG[0],
			vacio)).get_FFT(true)[0];
	//imagen solo fase:
	CImg<double> img_solo_fase = magfase2realimag(CImgList<double> (vacio,
			IMG[1])).get_FFT(true)[0];
	CImgDisplay dism1(img_solo_mag, "imagen solo magnitud");
	CImgDisplay dism2(img_solo_fase, "imagen solo fase");
	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
