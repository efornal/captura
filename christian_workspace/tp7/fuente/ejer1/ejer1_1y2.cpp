/*
 * ejer1_1y2.cpp
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
	const char *filename = cimg_option("-f", "../../imagenes/estanbul.tif",
			"ruta archivo imagen");

	float umbral = 40.0;
	CImg<double> img(filename); //imagen original
	//	img.resize_halfXY();
	CImgDisplay dispori(img, "imagen original");
	CImgDisplay disp(aplicar_roberts(img), "bd Roberts");
	CImgDisplay disp2(aplicar_laplaciano(img), "bd Lap(sin-diag)");
	CImgDisplay
			disp3(aplicar_laplaciano_condiagonales(img), "bd Lap(con-diag)");
	CImgDisplay disp4(aplicar_prewitt(img), "bd prewitt");
	CImgDisplay disp5(aplicar_prewitt_diagonal(img), "bd prewitt(con-diag)");
	CImgDisplay disp6(aplicar_sobel(img), "bd sobel");
	CImgDisplay disp7(aplicar_sobel_diagonal(img), "bd sobel(con-diag)");
	CImgDisplay disp1(aplicar_LoG(img), "bd LoG"); //fixme: porque sale con el fondo blanco? tengo que dar vuelta el umbral??
	//fixme: con log laplaciando y demas no aplico lo del gradiente.. deberia hacer el gradiente??
	aplicar_LoG(img).stats();
	while (!disp.is_closed()) {
		disp.wait();
		if (disp.is_keyARROWUP()) {
			umbral+=10;
			cout<<"umbral: "<<umbral<<endl;
		} else if (disp.is_keyARROWDOWN()) {
			umbral-=10;
			cout<<"umbral: "<<umbral<<endl;
		}
		aplicar_roberts(img, umbral, true).display(disp);
		disp.set_title("bd Roberts");

		aplicar_laplaciano(img, umbral, true).display(disp2);
		disp2.set_title("bd Lap(sin-diag)");

		aplicar_laplaciano_condiagonales(img, umbral, true).display(disp3);
		disp3.set_title("bd Lap(con-diag)");

		aplicar_prewitt(img, umbral, true).display(disp4);
		disp4.set_title("bd prewitt");

		aplicar_prewitt_diagonal(img, umbral, true).display(disp5);
		disp5.set_title("bd prewitt(con-diag)");

		aplicar_sobel(img, umbral, true).display(disp6);
		disp6.set_title("bd sobel");

		aplicar_sobel_diagonal(img, umbral, true).display(disp7);
		disp7.set_title("bd sobel(con-diag)");

		aplicar_LoG(img, umbral, true).display(disp1);
		disp1.set_title("bd LoG");
	}
	return 0;
}
