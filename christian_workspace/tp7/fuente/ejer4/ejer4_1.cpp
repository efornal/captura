/*
 * ejer6_1.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../../../tp4/fuente/lib4/proc_color.h"
#include "../../../tp3/fuente/lib3/mask.h"
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	const char *filename = cimg_option("-f", "../../imagenes/rosas.jpg",
			"ruta archivo imagen");
	float threshold = cimg_option("-umbral", 63.0, "threshold");
	float tol = cimg_option("-tolerancia", 0.2, "tolerancia");

	CImg<float> imagen(filename);

	CImgDisplay disp1(imagen, "imagen de futbol", 0);
	CImgDisplay disp2, dish1, dish2, dish3;

	// tome una muestra representativa del color a segmentar y calcule el centro de la esfera
	// (valor medio de cada compoennete)
	int posx = 149, posy = 135;

	float color_original[] = { imagen(posx, posy, 0, 0), imagen(posx, posy, 0,
			1), imagen(posx, posy, 0, 2) };

	CImg<float> binaria = segmentaRGB<float> (imagen, tol, imagen(posx, posy,
			0, 0), imagen(posx, posy, 0, 1), imagen(posx, posy, 0, 2),
			color_original);
	binaria.display(disp2);
	CImg<float> resultado = binaria.get_convolve(generar_mascara_promediadora<
			float> (7));
	CImgDisplay dispbaja(resultado, "imagen con pasa bajos");
	disp1.set_title(
			"use la ruedita del raton y el click - C para alternar entre color verdadero y color seteado");
	bool color_verd = false;
	CImgDisplay disp4;
	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyC()) {//cambia a color verdadero
			color_verd = !color_verd;
		} else if (disp1.is_keyARROWUP()) {
			threshold += 5.0;
			threshold = clipp<float> (threshold);
			cout << "Threshold: " << threshold << endl;
		} else if (disp1.is_keyARROWDOWN()) {
			threshold -= 5.0;
			threshold = clipp<float> (threshold);
			cout << "Threshold: " << threshold << endl;
		}
		if (disp1.button()) {
			posx = disp1.mouse_x();
			posy = disp1.mouse_y();
			color_original[0] = imagen(posx, posy, 0, 0);
			color_original[1] = imagen(posx, posy, 0, 1);
			color_original[2] = imagen(posx, posy, 0, 2);
		}
		binaria = segmentaRGB<float> (imagen, tol + (disp1.wheel() * 0.01),
				imagen(posx, posy, 0, 0), imagen(posx, posy, 0, 1), imagen(
						posx, posy, 0, 2), color_original, color_verd);
		resultado = binaria.get_convolve(
				generar_mascara_promediadora<float> (3));
		resultado.display(dispbaja);
		dispbaja.set_title("imagen con pasa bajos");
		binaria.display(disp2);
		cout << "Tolerancia: " << tol + (disp1.wheel() * 0.01) << endl;
		disp2.set_title("imagen segmentada");
		resultado.get_threshold(threshold).display(disp4);
		disp4.set_title("imagen con objetos grandes");
	}
	return 0;
}

/*




 cout<<"Threshold: "<<threshold<<endl;
 }
 return 0;
 */
