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
	CImg<double> imagen(300, 300, 1, 1);
	//cuadrado_centrado(imagen, 100, 100);
	circulo_centrado(imagen, 150);

	CImgList<double> tdf_imagen = imagen.get_FFT(); //obtengo la transofrmada

	CImg<double> tdf_imagen_real = tdf_imagen[0];
	CImg<double> tdf_imagen_imag = tdf_imagen[1];

	CImg<double> magnitud_imagen = (tdf_imagen_real.get_pow(2)
			+ tdf_imagen_imag.get_pow(2)).sqrt();

	CImgDisplay disp1;
	magnitud_imagen.log().normalize(0, 255).shift(magnitud_imagen.width()/2, magnitud_imagen.height()/2, 0, 0, 2).display(disp1);

	CImgDisplay disp2;
	CImg <unsigned char> modulo;
	magn_tdf(imagen, modulo, 1);
	modulo.display(disp2);
	while (!disp1.is_closed()){}

	return 0;
}
