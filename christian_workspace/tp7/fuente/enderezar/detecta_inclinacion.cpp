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
#include <vector>
#include "../lib7/CPDSI_segmentacion.h"
#include "../lib7/segmentacion.h"
#include "../../../tp2/fuente/lib2/operadores_logicos.h"

using namespace std;
using namespace cimg_library;
/*
 * http://users.cs.cf.ac.uk/Paul.Rosin/CM0311/dual2/hough.html
 * */
int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/letras1.tif",
			"ruta archivo imagen");

	CImg<double> img(filename); //imagen original
	img.rotate(30); //roto la imagen 30 grados a proposito...
	cout << "la inclinacion de la imagen es: " << detectar_inclinacion(img)
			<< endl;
	CImgDisplay disp(img, "imagen");
	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
