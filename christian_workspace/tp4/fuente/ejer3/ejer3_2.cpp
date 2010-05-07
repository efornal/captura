/*
 * ejer3_2.cpp
 *
 *  Created on: 21/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include <vector>
#include <string>
#include "../lib4/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<float> imagen("../../imagenes/a7v600-SE.gif");
	cout << "Use las teclas Arriba y abajo para cambiar de plate" << endl
			<< "Use las teclas derecha e izquierda para cambiar de imagen";
	CImg<float> la_paleta(256, 256, 1, 1);
	cimg_forXY(la_paleta, x,y)
		{
			la_paleta(x, y) = x; //genero imagen en tonos de grises
		}
	vector<vector<float> > paleta; //creo un vector de vectores
	cargar_paleta(paleta, "../../paletas/bone.pal");

	CImgDisplay disp1, disp2, disp3;

	CImg<float> imagen_con_paleta_aplicada = aplicar_paleta(imagen, 1);
	CImg<float> imagen_grises_con_paleta_aplicada = aplicar_paleta(la_paleta, 1);

	imagen.display(disp1);
	disp1.set_title("USAR TECLAS-imagen a la que se le aplica la paleta");

	imagen_con_paleta_aplicada.display(disp2);
	disp2.set_title("imagen con paleta aplicada");

	imagen_grises_con_paleta_aplicada.display(disp3);
	disp3.set_title("paleta aplicada a una imagen escala de grises");
	int nro_pal = 1;
	int nro_imagen = 1;

	while (!disp1.is_closed()) {
		disp1.wait();
		if (disp1.is_keyARROWUP()) {
			if (nro_pal >= 1 && nro_pal < 8)
				nro_pal++;
		} else if (disp1.is_keyARROWDOWN()) {
			if (nro_pal > 1 && nro_pal <= 8)
				nro_pal--;
		} else if (disp1.is_keyARROWRIGHT()) {//muestra siguiente imagen
			if (nro_imagen >= 1 && nro_imagen < 8) {
				nro_imagen++;
			}
		} else if (disp1.is_keyARROWLEFT()) { //volver a imagen anterior
			if (nro_imagen > 1 && nro_imagen <= 8) {
				nro_imagen--;
			}
		}
		//cargo imagen segun lo que se eligio con las flechas...
		switch (nro_imagen) {
		case 1:
			imagen.load("../../imagenes/a7v600-SE.gif");
			break;
		case 2:
			imagen.load("../../imagenes/camaleon.tif");
			break;
		case 3:
			imagen.load("../../imagenes/ej7a.tif");
			break;
		case 4:
			imagen.load("../../imagenes/earth.bmp");
			break;
		case 5:
			imagen.load("../../imagenes/huang1.jpg");
			break;
		case 6:
			imagen.load("../../imagenes/huang2.jpg");
			break;
		case 7:
			imagen.load("../../imagenes/reunion.tif");
			break;
		case 8:
			imagen.load("../../imagenes/rio.jpg");
			break;
		default:
			break;
		}

		imagen_con_paleta_aplicada = aplicar_paleta(imagen, nro_pal);
		imagen_grises_con_paleta_aplicada = aplicar_paleta(la_paleta, nro_pal);
		imagen.display(disp1);
		disp1.set_title("imagen a la que se le aplica la paleta");
		cout << "paleta: " << nro_pal << "           Imagen: " << nro_imagen
				<< endl;
		imagen_con_paleta_aplicada.display(disp2);
		disp2.set_title("imagen con paleta aplicada");

		imagen_grises_con_paleta_aplicada.display(disp3);
		disp3.set_title("paleta aplicada a una imagen escala de grises");
	}
	return 0;
}
