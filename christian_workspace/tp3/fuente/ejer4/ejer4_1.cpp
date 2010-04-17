/*
 * ejer4_1.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	//FIXME: no funciona
	CImg<float> imagen("../../imagenes/tablero.png");
	CImgDisplay disp1;
	generar_mascara<double> (0, 0, 10, 10).normalize(0, 255).display();
	cout << "varianza" << generar_mascara<double> (0, 0, 10, 10).variance()
			<< endl;
	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
