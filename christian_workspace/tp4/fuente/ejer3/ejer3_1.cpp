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
	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = x; //genero imagen en tonos de grises
		}

	vector<vector<float> > paleta; //creo un vector de vectores
	cargar_paleta(paleta, "../../paletas/bone.pal");

	CImgDisplay disp1, disp2;

	CImg<float> imagen_con_paleta_aplicada = aplicar_paleta(imagen, 1);

	imagen.display(disp1);
	disp1.set_title("USAR TECLAS-imagen a la que se le aplica la paleta");

	imagen_con_paleta_aplicada.display(disp2);
	disp2.set_title("imagen con paleta aplicada");

	int nro_pal = 1;

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWUP()) {
			if (nro_pal >= 1 && nro_pal < 8)
				nro_pal++;
		} else if (disp1.is_keyARROWDOWN()) {
			if (nro_pal > 1 && nro_pal <= 8)
				nro_pal--;
		}
		imagen_con_paleta_aplicada = aplicar_paleta(imagen, nro_pal);
		imagen.display(disp1);
		disp1.set_title("imagen a la que se le aplica la paleta");
		cout << "paleta: " << nro_pal << endl;
		imagen_con_paleta_aplicada.display(disp2);
		disp2.set_title("imagen con paleta aplicada");
	}
	return 0;
}
