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
#include "../lib5/lib5.h"
#include "../lib5/figuras.h"
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<double> imagen(1024, 1024, 1, 1);
	float f = 2.0; //frecuencia
	CImg<double> senoidal_rotada(1024, 1024, 1, 1);

	cimg_forXY(imagen, x, y)
		{
			imagen(x, y) = sin(2 * 3.1415 * f * x / 128.0) + 5;//+ sin(2 * 3.1415 * 10 * y/128.0);//+sin(2 * 3.1415 * 10 * x/128.0);
			//imagen(x,y) +=sin(2 * 3.1415 * 3 * y / 32.0);
			senoidal_rotada(x, y) = sin(2 * 3.1415 * 5 * x / 128.0) + 5;
			//			imagen(x,y) +=y+1;
		}

	//cimg_for3x3
	senoidal_rotada.rotate(45);
	senoidal_rotada.crop(400,400,600,600);
	imagen.crop(400,400,600,600);
	imagen+=senoidal_rotada;

	CImgDisplay disp1(imagen, "senoidal en x de frecuencia 2");
	CImg<unsigned char> magnitud_imagen(imagen);
	CImg<unsigned char> magnitud_imagen_no_centrada(imagen);
	magn_tdf(imagen, magnitud_imagen, true);
	magn_tdf(imagen, magnitud_imagen_no_centrada, false);
	CImgDisplay disp2(magnitud_imagen, "magnitud centrada de la imagen");
	magnitud_imagen.display();
	CImgDisplay disp3(magnitud_imagen_no_centrada,
			"magnitud no centrada de la imagen");
	while (!disp3.is_closed()) {
		disp3.wait();
	}
	return 0;
}
