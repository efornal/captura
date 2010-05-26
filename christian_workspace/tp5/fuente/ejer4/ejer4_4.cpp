/*
 * ejer4_4.cpp
 *
 *  Created on: 08/05/2010
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
//#include "../../../tp3/fuente/lib3/mask.h"
//#include "../../../tp4/fuente/lib4/CPDSI_functions.h"
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	const int tam_mask = cimg_option( "-size", 3, "tam mascara gaussiana" );
	const double varianza = cimg_option( "-varianza", 1.0, "varianza del filtro" );
	CImg<float> img(filename); //imagen original
	img.normalize(0, 255);

	CImgDisplay disporiginal(img, "imagen original");
	//fixme: esto todavia no anda ver!! - deberia ser pasa altos
	CImg <float> h = 1.0-gaussian_mask(tam_mask, varianza); //obtengo un filtro gaussiano de 3x3 con varianza 1

	//h.shift(h.width()/2, h.height()/2,0,0,2);
	CImg<float> filtrado_espacial = img.get_convolve(h);
	CImgDisplay esp(filtrado_espacial, "imagen filtrada en el dom espacial");

	CImg<float> magH(2 * img.width(), 2 * img.height(), 1, 1);
	CImg<float> filtrado_frecuencial = filtrar_desde_tiempo(img, h, magH);
	CImgDisplay fil(magH, "Resp. en Frec. del filtro");
	CImgDisplay resul(filtrado_frecuencial, "filtrado frecuencial");
	while (!disporiginal.is_closed()) {
		disporiginal.wait();
	}
	return 0;
}
