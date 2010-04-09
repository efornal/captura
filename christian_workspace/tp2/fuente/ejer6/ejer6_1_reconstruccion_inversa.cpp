/*
 * ejer6_1_reconstruccion_inversa.cpp
 *
 *  Created on: 07/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/plano_bit.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/huang.jpg");

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.

	CImg<unsigned char> resultado(imagen);
	resultado.fill(0);

	int plano_inicial = 7;
	int plano_final = 7;
	resultado = get_until_plan(imagen, plano_inicial, plano_final);
	cout << "Reconstruccion desde plano: " << plano_inicial
			<< "  hasta el plano: " << plano_final << endl;
	CImgDisplay disp(resultado, "Reconstruccion", 1);
	while (!disp.is_closed() && !disp.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP() && plano_inicial <7) { //aumentar plano bits
			resultado = get_until_plan(imagen, ++plano_inicial, plano_final);
		} else if (disp.is_keyARROWDOWN() && plano_final >0) {
			resultado = get_until_plan(imagen, --plano_inicial, plano_final);
		}
		cout << "Reconstruccion desde plano: " << plano_inicial
				<< "  hasta el plano: " << plano_final << endl;
		resultado.display(disp);
		disp.set_title("reconstruccion");
	}
	return 0;
}
