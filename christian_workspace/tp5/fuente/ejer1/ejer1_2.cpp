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
	CImg<double> imagen0(300, 300, 1, 1);
	CImg<double> imagen1(300, 300, 1, 1);
	CImg<unsigned char> mod_1(300, 300, 1, 1);
	CImg<double> imagen2(300, 300, 1, 1);
	CImg<unsigned char> mod_2(300, 300, 1, 1);
	CImg<double> imagen3(300, 300, 1, 1);
	CImg<unsigned char> mod_3(300, 300, 1, 1);

	circulo_centrado(imagen0, 100);
	cuadrado_centrado(imagen1, 30, 30);
	linea_vertical(imagen2, imagen2.width() / 2);
	linea_horizontal(imagen3, imagen3.height() / 3);

	CImgList<double> tdf_imagen = imagen0.get_FFT(); //obtengo la transofrmada

	CImg<double> tdf_imagen_real = tdf_imagen[0]; //parte real de la transformada
	CImg<double> tdf_imagen_imag = tdf_imagen[1]; //parte imaginaria

	CImg<double> magnitud_imagen = (tdf_imagen_real.get_pow(2)
			+ tdf_imagen_imag.get_pow(2)).sqrt(); //obtengo la magnitud de la transformada

	CImgList<double> lista0(imagen0,
			magnitud_imagen.log().normalize(0, 255).shift(
					magnitud_imagen.width() / 2, magnitud_imagen.height() / 2,
					0, 0, 2)); //muestreo la transformada shifteada
	CImgDisplay disp1(lista0, "Imagen y su transformada respectivamente", 0);

	magn_tdf(imagen1, mod_1, 1);
	magn_tdf(imagen2, mod_2, 1);
	magn_tdf(imagen3, mod_3, 1);

	CImgList<double> lista1(imagen1, mod_1);
	CImgList<double> lista2(imagen2, mod_2);
	CImgList<double> lista3(imagen3, mod_3);

	CImgDisplay disp2(lista1, "imagen y su transformada");
	CImgDisplay disp3(lista2, "imagen y su transformada");
	CImgDisplay disp4(lista3, "imagen y su transformada");
	/*CImg<unsigned char> modulo;
	 magn_tdf(imagen, modulo, 1); //transformada con la funcion de la catedra
	 CImgDisplay disp2(modulo, "modulo de la imagen", 0);*/
	while (!disp1.is_closed()) {
	}

	return 0;
}
