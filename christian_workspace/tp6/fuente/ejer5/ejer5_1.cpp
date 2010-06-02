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
#include "../../../tp3/fuente/lib3/mask.h"
//#include "../../../tp5/fuente/lib5/filtros.h"

#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/huang2_corrida.tif", "ruta archivo imagen" );
	CImg<double> g(filename); //imagen original

	/*
	 1-) creo una imagen impulso
	 2-) la aplico la funcion degradacion q te da el ejer por convolucion [...]1/n
	 3-) obtenes el impulso degradado
	 y listo...el sistema como es lti queda definido por la respuesta al impulso
	 entonces G(x,y) sería la TDF de la respuesta al impulso
	 H=G/A
	 donde A es una constante q ahi me cago
	 */

	CImgDisplay disp(g, "imagen huang corrida");
	CImg<double> h = generar_mascara_promediadora<float> (3);
	h = 1.0 / h;

	//sacar_movimiento(img, 1, 0.1,0.1).display(dii);//fixme: no anda
	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
