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
	CImg<unsigned char> img1("../../imagenes/letras1.tif");
	//CImg<unsigned char> img1("../../imagenes/earth.bmp");
	CImg<unsigned char> img2 = negativo(img1);
	CImgDisplay vent1(img1, "imagen original", 1), vent2(img2,
			"negativo de imagen original", 1), vent3(obtener_grafica_mapeo(-1,
			img2.max()), "grafica del negativo", 1);

	while (!vent1.is_closed() && !vent2.is_closed()) {
	}
	return 0;
}
