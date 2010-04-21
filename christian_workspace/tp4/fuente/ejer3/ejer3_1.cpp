/*
 * ejer3_1.cpp
 *
 *  Created on: 20/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include <vector>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen(256, 256, 1, 1);
	CImgDisplay disp1;
	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = x; //genero imagen en tonos de grises
		}
	imagen.normalize(0, 255.0);
	/*
	 * ../../paletas/bone.pal
	 ../../paletas/cool.pal
	 ../../paletas/copper.pal
	 ../../paletas/gray.pal
	 ../../paletas/hot.pal
	 ../../paletas/hsv.pal
	 ../../paletas/jet.pal
	 ../../paletas/pink.pal
	 ../../paletas/ver.txt
	 * */
	/*	char *paletas[10] = { "../../paletas/bone.pal", "../../paletas/bone.pal",
	 "../../paletas/cool.pal", "../../paletas/copper.pal",
	 "../../paletas/gray.pal", "../../paletas/hot.pal",
	 "../../paletas/hsv.pal", "../../paletas/jet.pal",
	 "../../paletas/pink.pal", "../../paletas/ver.txt" };*/

	/*	cout<<paleta[0][0]<<"    "<<paleta[0][1]<<"     "<< paleta[0][2]<<endl;
	 cout<<paleta[1][0]<<"    "<<paleta[1][1]<<"      "<<paleta[1][2]<<endl*/;

	vector<vector<float> > paleta; //creo un vecotr de vecotres
	cargar_paleta(paleta, "../../paletas/pink.pal");

	CImg<float> imagen_con_paleta_aplicada(imagen.width(), imagen.height(), 1,
			3);
	CImg<float> la_paleta(256, 1, 1, 3);
	cimg_forXY(imagen_con_paleta_aplicada, x, y)
		{ //es una lut:
			imagen_con_paleta_aplicada(x, y, 1, 0) = paleta[imagen(x, y)][0]*255; //canal rojo
			imagen_con_paleta_aplicada(x, y, 1, 1) = paleta[imagen(x, y)][1]*255; //canal verde
			imagen_con_paleta_aplicada(x, y, 1, 2) = paleta[imagen(x, y)][2]*255; //canal azul
		/*	la_paleta(x, y, 1, 0) = paleta[x][0]*255;
			la_paleta(x, y, 1, 1) = paleta[x][1]*255;
			la_paleta(x, y, 1, 2) = paleta[x][2]*255;*/

		}
//	la_paleta.normalize().display();
	imagen.display(disp1);


	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
