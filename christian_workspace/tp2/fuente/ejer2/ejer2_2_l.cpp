//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> imagen, im_log;
	imagen.load("../../imagenes/rmn.jpg");
	CImgDisplay disp1, disp2;
	int factor = 0;
	im_log = logaritmo(imagen, factor);
	disp1.set_title("grafica logaritmo variando el factor");
	im_log.display(disp1);
	cout << "Factor: " << factor << endl;
	obtener_grafica_mapeo_logaritmo(factor).display(disp2);
	while ((!disp1.is_closed() && !disp1.is_keyQ())) {
		disp1.wait();
		factor = clipp(factor); // me lo mantiene entre 0 y 255.. porque sin.. no hay limite...
		if (disp1.is_keyARROWDOWN())
			factor = clipp(--factor);
		else if (disp1.is_keyARROWUP()) {
			factor = clipp(++factor);
		}
		im_log = logaritmo(imagen, factor);
		disp1.set_title("grafica logaritmo variando el factor");
		im_log.display(disp1);
		cout << "Factor: " << factor << endl;
		obtener_grafica_mapeo_logaritmo(factor).display(disp2);
	}

	return 0;
}
