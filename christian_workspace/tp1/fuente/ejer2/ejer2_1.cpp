//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<unsigned char> imagen, imagen1, imagen2;

	imagen.load("../../imagenes/imagenA.tif");
	imagen.print();
	imagen.stats(); ////FIXME: que hace la funcion stats? parece no hacer nada!

	imagen1.load("../../imagenes/earth.bmp");
	imagen1.print();
	imagen1.stats();

	imagen2.load("../../imagenes/huang.jpg");
	imagen2.print();
	imagen2.stats();

	CImgDisplay vent1, vent2, vent3;
	imagen.display(vent1);
	vent1.set_title("imagen 0");

	imagen1.display(vent2);
	vent2.set_title("imagen 1");

	imagen2.display(vent3);
	vent3.set_title("imagen 2");


	while (!vent1.is_closed() && !vent2.is_closed() && !vent3.is_closed()) {
	}
	return 0;
}
