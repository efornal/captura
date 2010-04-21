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
	/*
	 * ../../paletas/bone.pal
	 * ../../paletas/cool.pal
	 * ../../paletas/copper.pal
	 * ../../paletas/gray.pal
	 * ../../paletas/hot.pal
	 * ../../paletas/hsv.pal
	 * ../../paletas/jet.pal
	 * ../../paletas/pink.pal
	 * */

	vector<vector<float> > paleta; //creo un vector de vectores
	cargar_paleta(paleta, "../../paletas/bone.pal");

	CImgDisplay disp1, disp2, disp3;
	CImg<float> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1,
			3);
	CImg<float> la_paleta(256, 256, 1, 3);
	//TODO: hacer funcion cargar paleta que lo aplique sobre unaimagen..
	cimg_forXY(imagen_con_paleta_aplicada, x, y)
		{ //es una lut:
			imagen_con_paleta_aplicada(x, y, 1, 0) = paleta[imagen(x, y)][0]
					* 255.0; //canal rojo
			imagen_con_paleta_aplicada(x, y, 1, 1) = paleta[imagen(x, y)][1]
					* 255.0; //canal verde
			imagen_con_paleta_aplicada(x, y, 1, 2) = paleta[imagen(x, y)][2]
					* 255.0; //canal azul

			la_paleta(x, y, 1, 0) = paleta[x][0] * 255;
			la_paleta(x, y, 1, 1) = paleta[x][1] * 255;
			la_paleta(x, y, 1, 2) = paleta[x][2] * 255;
		}
	/*FIXME: porque la ultima linea de las imagens se ven mal!?
	 * porque en la paleta si bien en el archivo tiene valores 0 cuando la despliego no aparece dicho valor?*/
	la_paleta.print();
	imagen.display(disp1);
	disp1.set_title("imagen a la que se le aplica la paleta");

	imagen_con_paleta_aplicada.display(disp2);
	disp2.set_title("imagen con paleta aplicada");

	la_paleta.display(disp3);
	disp3.set_title("la paleta");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
