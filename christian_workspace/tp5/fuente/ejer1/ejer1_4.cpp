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
	CImg<float> imagen("../../imagenes/a7v600-SE.gif");
	imagen.print();
	cout << "Use las teclas Arriba y abajo para cambiar de plate" << endl
			<< "Use las teclas derecha e izquierda para cambiar de imagen";
	int nro_imagen = 1;
	CImg<unsigned char> magnitudFFT(imagen.width(), imagen.height(), 1, 1);
	magn_tdf(imagen, magnitudFFT, true);
	CImgDisplay disp1(imagen, "imagen");
	CImgDisplay disp2(magnitudFFT, "magnitud de la transforamda");

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWUP()) {//muestra siguiente imagen
			if (nro_imagen >= 1 && nro_imagen < 8) {
				nro_imagen++;
			}
		} else if (disp1.is_keyARROWDOWN()) { //volver a imagen anterior
			if (nro_imagen > 1 && nro_imagen <= 8) {
				nro_imagen--;
			}
		}
		//cargo imagen segun lo que se eligio con las flechas...
		switch (nro_imagen) {
		case 1:
			imagen.load("../../imagenes/a7v600-SE.gif").resize(375,375);
			break;
		case 2:
			imagen.load("../../imagenes/camaleon.tif").resize(375,375);
			break;
		case 3:
			imagen.load("../../imagenes/ej7a.tif").resize(375,375);
			break;
		case 4:
			imagen.load("../../imagenes/earth.bmp").resize(375,375);
			break;
		case 5:
			imagen.load("../../imagenes/huang1.jpg").resize(375,375);
			break;
		case 6:
			imagen.load("../../imagenes/huang2.jpg").resize(375,375);
			break;
		case 7:
			imagen.load("../../imagenes/reunion.tif").resize(375,375);
			break;
		case 8:
			imagen.load("../../imagenes/rio.jpg").resize(375,375);
			break;
		default:
			break;
		}

		magn_tdf(imagen, magnitudFFT, true);
		imagen.display(disp1);
		disp1.set_title("imagen");
		magnitudFFT.display(disp2);
		disp2.set_title("magnitud de la transforamda");
	}
	//fixme: commo interpretas las magnitudes en las imagenes!! ???
	return 0;
}
