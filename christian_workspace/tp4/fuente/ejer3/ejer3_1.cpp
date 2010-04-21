/*
 * ejer3_1.cpp
 *
 *  Created on: 20/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include <vector>
#include <string>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen(256, 256, 1, 1);
	CImg<float> la_paleta(256, 256, 1, 1, 255.0);

	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = x; //genero imagen en tonos de grises
		}

	vector<vector<float> > paleta; //creo un vector de vectores
	cargar_paleta(paleta, "../../paletas/bone.pal");

	CImgDisplay disp1, disp2, disp3;

	CImg<float> imagen_con_paleta_aplicada=aplicar_paleta(imagen, 1);
	la_paleta=aplicar_paleta(la_paleta, 1);

	imagen.display(disp1);
	disp1.set_title("imagen a la que se le aplica la paleta");

	imagen_con_paleta_aplicada.display(disp2);
	disp2.set_title("imagen con paleta aplicada");


	imagen_con_paleta_aplicada.display(disp3);
	disp3.set_title("paleta aplicada a una imagen blanca");
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
