#define UNICODE
#include <CImg.h>
#include <iostream>
//#include "../lib4/CPDSI_functions.h"
#include "../lib4/proc_color.h"

using namespace cimg_library;
using namespace std;

//Ejercico de mauro...
int main(int argc, char *argv[]) {

	const char *im = cimg_option( "-f", "../../imagenes/rostro3.png", "imagen" );

	CImg<double> imagen(im);
	CImgDisplay d_imagen;

	double radio = 0.1;
	int norma = 2, entorno = 0; // si le pongo entorno=0 tomaria de un solo pixel no haria el promedio de hsi

	double h, s, i;
	int x, y;
	imagen.display(d_imagen);

	while (!d_imagen.is_closed()) {
		d_imagen.wait_all();

		if (d_imagen.button() && d_imagen.mouse_x() >= 0 && d_imagen.mouse_y()
				>= 0) {
			x = d_imagen.mouse_x();
			y = d_imagen.mouse_y();
			promedio_valores_hsi(imagen, h, s, i, entorno, x, y);
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyN()) {
			++norma %= 3;
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyARROWUP()) {
			radio += 0.05;
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyARROWDOWN()) {
			radio -= 0.05;
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyARROWLEFT()) {
			--entorno;
			promedio_valores_hsi(imagen, h, s, i, entorno, x, y);
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyARROWRIGHT()) {
			++entorno;
			promedio_valores_hsi(imagen, h, s, i, entorno, x, y);
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
		if (d_imagen.is_keyR()) {
			radio = 6;
			norma = 0;
			entorno = 2;
			promedio_valores_hsi(imagen, h, s, i, entorno, x, y);
			segmentar_hs(imagen, h, s, radio, norma).display(d_imagen);
		}
	}
	return 0;
}
