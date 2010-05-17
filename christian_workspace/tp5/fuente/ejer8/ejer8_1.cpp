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
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/camaleon.tif", "ruta archivo imagen" );
	CImg<> img(filename);
	CImgDisplay disp(img, "imagen original");
	float A = 10.0;
	float varianza = 1.0;
	float b=1.0;
	float a=0.0;
	CImg<float> filtrada = aplicar_PA_alta_potencia<float> (img, varianza, A);
	CImg<float> filtrada_enfasis= aplicar_PA_enfasis_AF(img, varianza, a, b);
	CImgDisplay disp1(filtrada, "imagen filtrada con Alta potencia");
	CImgDisplay disp2(filtrada_enfasis, "imagen filtrada con Enfasis");
	while (!disp1.is_closed()) {
		if (disp1.is_keyARROWUP()) {
			varianza += 0.1;
		} else if (disp1.is_keyARROWDOWN()) {
			varianza -= 0.1;
		} else if (disp1.is_keyARROWRIGHT()) {
			A++;
		} else if (disp1.is_keyARROWLEFT()) {
			A--;
		} else if (disp1.is_keyB()){
			b++;
		} else if (disp1.is_keyG()){
			b--;
		} else if (disp1.is_keyE()){
			a++;
		} else if (disp1.is_keyD()){
			a--;
		}
		if (disp1.is_event()) {
			filtrada = aplicar_PA_alta_potencia<float> (img, varianza, A);
			filtrada.log().display(disp1); //fixme: normalizo .. aplico log?
			filtrada_enfasis= aplicar_PA_enfasis_AF(img, varianza, a, b);
			filtrada_enfasis.log().display(disp2); //fixme: normalizo .. aplico log?
			disp2.set_title("imagen filtrada con Enfasis usar B G E D");
			disp1.set_title("imagen filtrada con Alta potencia - usar flechas");
			cout << "A: " << A << "     - Varianza: " << varianza <<" ### a: "<<a<<"     - b: "<<b<<endl;
		}
		//fixme: compare con la alta potencia con la que se obtiene al aplicar el el dominio espacial.. ver el 3..
		// comparar con el de alta potencia en el dominio espacial? no se supone que va a adar lo mismo?
	}
	return 0;
}
