/*
 * ejer7_1.cpp
 *
 *  Created on: 21/05/2010
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
	const char *filename = cimg_option("-f", "../../imagenes/estanbul.tif",
			"ruta archivo imagen");

	CImg<double> img(filename); //imagen original
	img.resize_halfXY();
	CImgDisplay dispori(img, "imagen original");
	CImgDisplay disp(aplicar_roberts(img), "bd Roberts");
	CImgDisplay disp1(aplicar_LoG(img), "bd LoG"); //fixme: porque sale con el fondo blanco?
	//fixme: con log laplaciando y demas no aplico lo del gradiente.. deberia hacer el gradiente??
	CImgDisplay disp2(aplicar_laplaciano(img), "bd Lap(sin-diag)");
	CImgDisplay
			disp3(aplicar_laplaciano_condiagonales(img), "bd Lap(con-diag)");
	CImgDisplay disp4(aplicar_prewitt(img), "bd prewitt");
	CImgDisplay disp5(aplicar_prewitt_diagonal(img), "bd prewitt(con-diag)");
	CImgDisplay disp6(aplicar_sobel(img), "bd sobel");
	CImgDisplay disp7(aplicar_sobel_diagonal(img), "bd sobel(con-diag)");

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
