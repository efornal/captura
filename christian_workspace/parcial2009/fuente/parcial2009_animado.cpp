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
#include "../../tp7/fuente/lib7/CPDSI_segmentacion.h"
#include "../../tp7//fuente/lib7/segmentacion.h"
#include "../../tp2/fuente/lib2/operadores_logicos.h"
#include "../../tp6/fuente/lib6/restauracion.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option("-f", "./CPDSI_Parcial_Practica_2009/corrientes_ruidogris.jpg",
							"ruta archivo imagen");
	int x = cimg_option("-x", 200, "posicion en x del pixel a segemntar");
	int y = cimg_option("-y", 200, "posicion en y del pixel a segemntar");
	int tam_mascara = cimg_option("-sizemask", 9, "Tam de la mascara");
	int d = cimg_option("-dfiltro", 1.0, "d del filtro media alfa recortado");
	float tolerancia = cimg_option("-tol", 50.0, "tolerancia");
	int cantidad_vecinos = cimg_option("-vecinos", 4, "cant vecinos 4 u 8");

	CImg<float> imagen(filename);
	imagen = filtrado_alfa_recortado(imagen, d, tam_mascara);
	imagen = imagen.channel(0);
	CImgDisplay disp1(imagen, "imagen");

	CImg<float> imagen_segmentada = segmentar(imagen, x, y, tolerancia,
			cantidad_vecinos);
	CImgDisplay disp2(imagen_segmentada, "imagen segmentada");

	CImg<float> original_segmentada = binaria_a_original(imagen_segmentada,
			imagen);
	CImgDisplay disp3(original_segmentada, "imagen orig. segmentada");
	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.button()) {
			x = disp1.mouse_x();
			y = disp1.mouse_y();
			cout << "X: " << imagen(x, y) << endl;
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

		original_segmentada = binaria_a_original(imagen_segmentada, imagen);
		original_segmentada.display(disp3);
		disp3.set_title("imagen original segmentada");
	}
	return 0;
}
