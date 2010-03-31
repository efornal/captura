//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/imagenD.tif"); //cargo la imagen
	int c = 1;
	CImgDisplay disp1, disp2, disp3;

	imagen.display(disp2);

	disp2.set_title("Imagen original");

	for (int a = 0; a <= 255; a++) {

		CImg<unsigned char> imagen_modificada = lut(imagen, a, c, false); // sin clipping
		disp1.set_title("variando a");
		imagen_modificada.display(disp1);

		disp3.set_title("rango");
		obtener_grafica_mapeo(a, c).display(disp3);
		cout << "Salida=" << a << "*entrada+" << c << endl;
		while (!disp1.button()) {
		}
		sleep(0.7);
	}

	for (int a = 255; c >= 0; c--) {

		CImg<unsigned char> imagen_modificada = lut(imagen, a, c, false); // sin clipping
		disp1.set_title("variando a");
		imagen_modificada.display(disp1);

		disp3.set_title("rango");
		obtener_grafica_mapeo(a, c).display(disp3);
		cout << "Salida=" << a << "*entrada+" << c << endl;
		while (!disp1.button()) {
		}
		sleep(0.7);
	}
	return 0;
}
