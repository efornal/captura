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
	const char *filename = cimg_option("-f", "../../imagenes/mosquito.jpg",
			"ruta archivo imagen");

	CImg<double> img(filename); //imagen original
	float desvio = 0.0;
	CImgDisplay dispsucia;
	//contarminacion con ruida
	CImg<double> imagen_sucia = img.get_noise(desvio, 0); //0 indica ruido gaussiano
	CImgDisplay dispori(img, "imagen original");
	CImgDisplay disp(aplicar_roberts(img), "bd Roberts");
	CImgDisplay disp1(aplicar_LoG(img), "bd LoG");
	CImgDisplay disp2(aplicar_laplaciano(img), "bd Lap(sin-diag)");
	CImgDisplay
			disp3(aplicar_laplaciano_condiagonales(img), "bd Lap(con-diag)");
	CImgDisplay disp4(aplicar_prewitt(img), "bd prewitt");
	CImgDisplay disp5(aplicar_prewitt_diagonal(img), "bd prewitt(con-diag)");
	CImgDisplay disp6(aplicar_sobel(img), "bd sobel");
	CImgDisplay disp7(aplicar_sobel_diagonal(img), "bd sobel(con-diag)");

	while (!dispori.is_closed()) {
		dispori.wait();
		if (dispori.is_keyARROWUP()) {
			desvio += 0.1;
			imagen_sucia = img.get_noise(desvio, 0); //0 indica ruido gaussiano
		} else if (dispori.is_keyARROWDOWN()) {
			desvio -= 0.1;
			imagen_sucia = img.get_noise(desvio, 0); //0 indica ruido gaussiano
		}
		cout << "Varianza ruido gaussiano: " << desvio << endl;
		imagen_sucia.display(dispsucia);
		dispsucia.set_title("imagen sucia - aca usar teclas");

		aplicar_roberts(imagen_sucia).display(disp);
		disp.set_title("bd Roberts");

		aplicar_LoG(imagen_sucia).display(disp1);
		disp1.set_title("bd LoG");

		aplicar_laplaciano(imagen_sucia).display(disp2);
		disp2.set_title("bd Lap(sin-diag)");

		aplicar_laplaciano_condiagonales(imagen_sucia).display(disp3);
		disp3.set_title("bd Lap(con-diag)");

		aplicar_prewitt(imagen_sucia).display(disp4);
		disp4.set_title("bd prewitt");

		aplicar_prewitt_diagonal(imagen_sucia).display(disp5);
		disp5.set_title("bd prewitt(con-diag)");

		aplicar_sobel(imagen_sucia).display(disp6);
		disp6.set_title("bd sobel");

		aplicar_sobel_diagonal(imagen_sucia).display(disp7);
		disp7.set_title("bd sobel(con-diag)");
	}
	return 0;
}
