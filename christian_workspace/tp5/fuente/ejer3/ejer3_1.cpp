/*
 * ejer3_1.cpp
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
#include "../lib5/lib5.h"
#include "../lib5/figuras.h"
#include "../lib5/filtros.h"
//#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	//fixme: porque no se nota la variacion al hacer el filtrado con los diferentes tamanios? sera porque el tam del impulso es siempre el mismo?
	CImg<double> img1(25, 25, 1, 1, 0), img2(100, 100, 1, 1, 0), img3(200, 200,
			1, 1, 0);
	cuadrado_centrado<double> (img1, 5.0, 5.0, img1.width() / 2.0,
			img1.height() / 2.0, 0);
	cuadrado_centrado<double> (img2, 5.0, 5.0, img2.width() / 2.0,
			img2.height() / 2.0, 0);
	cuadrado_centrado<double> (img3, 5.0, 5.0, img3.width() / 2.0,
			img3.height() / 2.0, 0);

	//muestro imagen original, filtro que se aplica centrado e imagen filtrada
	//filtro 25x25:
	CImgDisplay disp(img, "imagen original");
	CImgDisplay disp1(get_magnitud<double> (img1, true),
			"magnitud del filtro centrado - 25x25");
	CImgDisplay disp2(img.get_convolve(img1),
			"imagen filtrada con filtro centrado - 25x25");

	//filtro 100x100:

	CImgDisplay disp3(get_magnitud<double> (img2, true),
			"magnitud del filtro centrado - 100x100");
	CImgDisplay disp4(img.get_convolve(img2),
			"imagen filtrada con filtro centrado - 100x100");

	//filtro 200x200:
	CImgDisplay disp5(get_magnitud<double> (img3, true),
			"magnitud del filtro centrado - 200x200");
	CImgDisplay disp6(img.get_convolve(img3),
			"imagen filtrada con filtro centrado - 200x200");

	while ((!disp.is_closed() && !disp.is_keyQ())) {
		disp.wait();
	}

	return 0;
}
