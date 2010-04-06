//============================================================================
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include <string.h>

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> img1("../../imagenes/earth.bmp");

	CImgDisplay vent1, vent2, vent3;
	vent1.set_title("original");
	img1.display(vent1); //ventana 1 muestreo la imagen original

	for (int factor = 0; factor < 100; ++factor) {

		CImg<unsigned char> img2 = lut_tramos(img1, 100, 200, 0, factor);
		vent2.set_title("imagen modificada con estiramiento o compresion segun factor");
		img2.display(vent2);

		vent3.set_title("factor");
		cout<<"Factor: "<<factor<<endl;
		obtener_grafica_mapeo_tramos(100, 200, factor).display(vent3);
		while (!vent2.button()) {
		}
		sleep(0);
	}
	return 0;
}
