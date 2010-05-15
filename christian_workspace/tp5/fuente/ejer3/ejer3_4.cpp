/*
 * ejer3_4.cpp
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
/*
#include "../lib5/lib5.h"
#include "../lib5/figuras.h"
#include "../../../tp3/fuente/lib3/mask.h"
*/
#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<double> img(filename); //imagen original
	img.normalize(0, 255);
	CImgDisplay disporiginal(img, "imagen original");

	double varianza = 0.1;
//fixme: porque esto no da igual al filtro que se aplica en frecuencia en el ejercicio 5?
	CImg<double> H(img.width(), img.height(), 1, 1);
	CImgDisplay disp1, disp2;
	CImg<double> filtrada = aplicar_Gaussiano_PB<double> (img, H, varianza);
	filtrada.display(disp1);
	disp1.set_title("imagen filtrada");
	H.display(disp2);
	disp2.set_title("Filtro que se aplica");
	while (!disp1.is_closed()) {
		if (disp1.is_keyARROWUP()) {
			varianza+=0.01;
		} else if (disp1.is_keyARROWDOWN()) {
			varianza-=0.01;
		}
		filtrada = aplicar_Gaussiano_PB<double> (img, H, varianza);
		filtrada.display(disp1);
		disp1.set_title("imagen filtrada");

		H.display(disp2);
		disp2.set_title("Filtro que se aplica");
		cout << "Varianza: " << varianza << endl;
	}
	return 0;
}
