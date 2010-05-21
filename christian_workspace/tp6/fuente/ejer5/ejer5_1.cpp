/*
 * ejer6_1.cpp
 *
 *  Created on: 13/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include "../lib6/restauracion.h"
#include "../../../tp5/fuente/lib5/filtros.h"
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2_corrida.tif", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	//fixme: no anda
	CImgDisplay disp(img, "imagen huang corrida");

	sacar_movimiento(img, 1, 0.1,0.1).display(dii);
	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
