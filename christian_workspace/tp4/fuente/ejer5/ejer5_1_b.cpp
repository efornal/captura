/*
 * ejer5_1_b.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen_oscura("../../imagenes/chairs_oscura.jpg"); //cargo la imagen

	imagen_oscura.resize(300, 300);
	int dx = imagen_oscura.width();
	int dy = imagen_oscura.height();

	CImg<float> imagen_oscura_R(dx, dy, 1, 3), imagen_oscura_G(dx, dy, 1, 3),
			imagen_oscura_B(dx, dy, 1, 3);
	descomponer_rgb(imagen_oscura, imagen_oscura_R, imagen_oscura_G,
			imagen_oscura_B); //descompongo la imagen en 3 canales

	CImgList<float> lista(imagen_oscura, imagen_oscura_R, imagen_oscura_G,
			imagen_oscura_B);
	CImgDisplay disp1(lista, "imagen oscura, canal R, canal G, canal B", 0);

	//------------------------------------------------------------
	//ecualizar cada componentee por serparado y mostrar:
	CImg<float> imagen_oscura_ecualizada(imagen_oscura), imagen_oscura_R_eq(dx,
			dy, 1, 3), imagen_oscura_G_eq(dx, dy, 1, 3), imagen_oscura_B_eq(dx,
			dy, 1, 3);
	descomponer_rgb<float> (imagen_oscura_ecualizada, imagen_oscura_R_eq,
			imagen_oscura_G_eq, imagen_oscura_B_eq, true);
	CImgList<float> lista1(imagen_oscura_ecualizada, imagen_oscura_R_eq,
			imagen_oscura_G_eq, imagen_oscura_B_eq);
	CImgDisplay
			disp2(
					lista,
					"imagen oscura ecualizada, canal R ecualizado, canal G ecualizado, canal B ecualizado",
					0);
	while (!disp1.is_closed()) {
	};
	return 0;
}
