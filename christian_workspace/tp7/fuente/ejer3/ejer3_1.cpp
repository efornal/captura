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

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename =
			cimg_option("-f", "../../imagenes/flowers_oscura.tif",
					"ruta archivo imagen");
	CImg<float> imagen(filename);
	CImgDisplay disp1(imagen, "imagen", 0);
	CImgDisplay disp2, dish1, dish2, dish3;

	//imagen.normalize(0,1);
	CImg<> ladelabel = label_cc(imagen.channel(0));
	//ladelabel.display();
	//ladelabel.display(disp2);
	//ladelabel.print();

	//b---------------------------------------------------------------------------------------
	// tome una muestra representativa del color a segmentar y calcule el centro de la esfera
	// (valor medio de cada compoennete)

	int posx = 149, posy = 135;
	float color_original[] = { imagen(posx, posy, 0, 0), imagen(posx, posy, 0,
			1), imagen(posx, posy, 0, 2) };

	while (!disp1.is_closed()) {
		disp1.wait();
	}

	/*	float tol = 0.5;


	 segmentaRGB<float> (imagen, tol, imagen(posx, posy, 0, 0), imagen(posx,
	 posy, 0, 1), imagen(posx, posy, 0, 2), color_original).display(
	 disp2);
	 disp1.set_title(
	 "use la ruedita del raton y el click - C para alternar entre color verdadero y color seteado");
	 bool color_verd = false;
	 while (!disp1.is_closed()) {
	 disp1.wait();
	 if (disp1.is_keyC()) {//cambia a color verdadero
	 color_verd = !color_verd;
	 }
	 if (disp1.button()) {
	 posx = disp1.mouse_x();
	 posy = disp1.mouse_y();
	 color_original[0] = imagen(posx, posy, 0, 0);
	 color_original[1] = imagen(posx, posy, 0, 1);
	 color_original[2] = imagen(posx, posy, 0, 2);
	 }
	 segmentaRGB<float> (imagen, tol + (disp1.wheel() * 0.01), imagen(posx,
	 posy, 0, 0), imagen(posx, posy, 0, 1),
	 imagen(posx, posy, 0, 2), color_original, color_verd).display(
	 disp2);
	 cout << "Tolerancia: " << tol + (disp1.wheel() * 0.01) << endl;
	 disp2.set_title("imagen segmentada");
	 }*/
	return 0;
}
