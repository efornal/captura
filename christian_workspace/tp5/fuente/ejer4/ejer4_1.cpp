/*
 * ejer4_1.cpp
 *
 *  Created on: 11/05/2010
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
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	//fixme: porque no se nota la variacion al hacer el filtrado con los diferentes tamanios? sera porque el tam del impulso es siempre el mismo?
	CImg<double> img1(25, 25, 1, 1), img2(100, 100, 1, 1), img3(200, 200,
			1, 1);
	unsigned char negro[] = {0,0,0};
	img1.fill(255.0);
	img2.fill(255.0);
	img3.fill(255.0);

    img1.draw_rectangle(11,11,15,15,negro);
    img2.draw_rectangle(48,48,52,52,negro);
    img3.draw_rectangle(98,98,102,102,negro);

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
