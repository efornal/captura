/*
 * ejer6_1.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib2/lut.h"
#include "../lib2/plano_bit.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/tablero.png");

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.
	int plano = 0;
	CImgDisplay disp(plano_de_bit(imagen, plano), "plano 0 = 0000 0001", 1);
	cout << endl;
	while (!disp0.is_closed() && !disp0.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP()) { //aumentar plano bits
			plano = clipp_plano(++plano);
		} else if (disp.is_keyARROWDOWN()) {
			plano = clipp_plano(--plano);
		}
		disp.display(plano_de_bit(imagen, plano));
		disp.set_title("planos 0=>7");
		cout << "Plano: " << plano<<endl;
	}

	while ((!disp.is_closed() && !disp.is_keyQ())) {
	}
	return 0;
}
