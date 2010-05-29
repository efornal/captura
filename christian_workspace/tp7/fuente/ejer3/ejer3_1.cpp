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
//#include "../../../tp4/fuente/lib4/proc_color.h"
#include "../lib7/CPDSI_segmentacion.h"
#include "../lib7/segmentacion.h"
#include "../../../tp2/fuente/lib2/operadores_logicos.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option("-f", "../../imagenes/bone.tif",
			"ruta archivo imagen");
	CImg<float> imagen(filename);
	imagen = imagen.channel(0);
	CImgDisplay disp1(imagen, "imagen");
	int x = 200;
	int y = 200;
	float tolerancia = 50.0;
	int cantidad_vecinos = 4;

	CImg<float> imagen_segmentada = segmentar(imagen, x, y, tolerancia,
			cantidad_vecinos);
	CImgDisplay disp2(imagen_segmentada, "imagen segmentada");

	CImg<float> original_segmentada(imagen);

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.button()) {
			x = disp1.mouse_x();
			y = disp1.mouse_y();
			cout<<"X: "<<imagen(x,y)<<endl;
		} else if (disp1.is_keyV()) { //alterna entre 4 u 8 vecinos
			(cantidad_vecinos == 4) ? cantidad_vecinos = 8 : cantidad_vecinos
					= 4;
			cout << "cantidad de vecinos: " << cantidad_vecinos << endl;
		} else if (disp1.is_keyARROWUP()) {
			tolerancia++;
			cout << "Tolerancia: " << tolerancia << endl;
		} else if (disp1.is_keyARROWDOWN()) {
			tolerancia--;
			cout << "Tolerancia: " << tolerancia << endl;
		}
		imagen_segmentada = segmentar(imagen, x, y, tolerancia,
				cantidad_vecinos);
		imagen_segmentada.display(disp2);
		disp2.set_title("imagen segmentada");
	}
	return 0;
}
