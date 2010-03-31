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
	imagen.load("../../imagenes/earth.bmp"); //cargo la imagen
	CImgDisplay disp1, disp2, disp3;
	int a = 1;
	imagen.display(disp2);

	disp2.set_title("Imagen original");

	for (int c = 0; c <= 255; c++) {

		CImg<unsigned char> imagen_modificada = lut(imagen, a, c, false); // sin clipping
		disp1.set_title("variando c");
		imagen_modificada.display(disp1);

		disp3.set_title("rango");
		obtener_grafica_mapeo(a, c).display(disp3);
		cout << "Salida=" << a << "*entrada+" << c << endl;

		while (!disp1.button()){}

		sleep(0.5);
	}

	for (int c = 255; c >= 0; c--) {

		CImg<unsigned char> imagen_modificada = lut(imagen, a, c, false); // sin clipping
		disp1.set_title("variando c");
		imagen_modificada.display(disp1);

		disp3.set_title("rango");
		obtener_grafica_mapeo(a, c).display(disp3);
		cout << "Salida=" << a << "*entrada+" << c << endl;
		while (!disp1.button()){}
		sleep(0.5);
	}
	return 0;
}
