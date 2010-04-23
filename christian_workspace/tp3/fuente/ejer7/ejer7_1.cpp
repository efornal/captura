/*
 * ejer7_1.cpp
 *
 *  Created on: 08/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	int nlevels = 255;
	CImg<unsigned char> imagen("../../imagenes/ej7a.tif");
	CImg<unsigned char> imagen_ecualizada = imagen.get_equalize(nlevels);
	CImgDisplay disp1, disp2, disp3, disp4;

	imagen.display(disp1);
	disp1.set_title("imagen original");

	imagen_ecualizada.display(disp2);
	disp2.set_title("imagen ecualizada globalmente");

	CImg<unsigned char> imagen_ecualizada_localmente(imagen);
	imagen_ecualizada_localmente.display(disp3);

	CImg<unsigned char> auxiliar(imagen);
	unsigned char rojo[] = { 255, 0, 0 };
	int deltax = 20;
	int deltay = 20;
	while (!disp3.is_closed()) {
		disp3.wait();
		{
			if (disp3.is_keyPAGEUP()) {
				deltax++;
				deltay++;
			} else if (disp1.is_keyPAGEDOWN()) {
				deltax--;
				deltay--;
			}
			/*imagen_ecualizada_localmente.draw_rectangle(disp3.mouse_x(),
			 disp3.mouse_y(), disp3.mouse_x() + deltax, disp3.mouse_y()
			 + deltay, rojo, 1, 1);*/
//TODO: aplicar la mascara
			auxiliar.draw_image(disp3.mouse_x(), disp3.mouse_y(), 0, 0, imagen_ecualizada_localmente.get_crop(disp3.mouse_x(),
							disp3.mouse_y(), disp3.mouse_x() + deltax,
							disp3.mouse_y() + deltay).get_normalize(0, 255), imagen, 1,
					1);
			imagen_ecualizada_localmente.display(disp3);
		}
	}
	return 0;
}
