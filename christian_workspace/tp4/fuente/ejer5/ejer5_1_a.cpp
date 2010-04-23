/*
 * ejer5_1.cpp
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

	imagen_oscura.resize(200,200);
	int dx=imagen_oscura.width();
	int dy=imagen_oscura.height();

	CImg<float> imagen_oscura_R(dx,dy,1,3), imagen_oscura_G(dx,dy,1,3), imagen_oscura_B(dx,dy,1,3);
	cimg_forXY(imagen_oscura_R,x,y){
		imagen_oscura_R(x,y,0,0)= imagen_oscura(x,y,0,0);//canal rojo
		imagen_oscura_R(x,y,0,1)= 0; //POSTA: guarda porque la cimg_forXY te hace para todos los C si no le especificas nada!!
		imagen_oscura_R(x,y,0,2)= 0;
		imagen_oscura_G(x,y,0,1)= imagen_oscura(x,y,0,1);//canal rojo
		imagen_oscura_B(x,y,0,2)= imagen_oscura(x,y,0,2);//canal rojo
	}

	CImgList <float> lista (imagen_oscura, imagen_oscura_R, imagen_oscura_G, imagen_oscura_B);
	CImgDisplay disp1(lista, "imagen oscura, canal R, canal G, canal B",0);






	while (!disp1.is_closed()) {
	};
	return 0;
}
