/*
 * ejer9_1c.cpp
 *
 *  Created on: 15/05/2010
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

//#include "../lib5/lib5.h"
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	//fixme: esto no funciona! y falta hacer el de alta enfasis!
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/camaleon.tif", "ruta archivo imagen" );
	CImg<> img(filename);
	CImgDisplay disp(img, "imagen original");
	float A = 10.0;
	float varianza = 1.0;
	CImg<float> filtrada = aplicar_PA_alta_potencia<float> (img, varianza, A);

	CImgDisplay disp1(filtrada, "imagen filtrada con Alta potencia");
	while (!disp1.is_closed()) {
		if (disp1.is_keyARROWUP()) {
			varianza += 0.1;
		} else if (disp1.is_keyARROWDOWN()) {
			varianza -= 0.1;
		} else if (disp1.is_keyARROWRIGHT()) {
			A++;
		} else if (disp1.is_keyARROWLEFT()) {
			A--;
		}
		if (disp1.is_event()) {
			filtrada = aplicar_PA_alta_potencia<float> (img, varianza, A);
			filtrada.log().normalize(0,255).display(disp1);
			disp1.set_title("imagen filtrada con Alta potencia");
			cout << "A: " << A << "     - Varianza: " << varianza << endl;
		}
	}
	return 0;
}
