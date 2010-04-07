/*
 * ejer6_1_reconstruccion.cpp
 *
 *  Created on: 06/04/2010
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

	CImg<unsigned char> planos[8]; //imagenes

	CImgDisplay disp0(imagen, "imagen original", 1); // el 1 es para que normalice.
	int plano = 0;

	for (int i = 0; i <= 7; i++) {
		planos[i] = plano_de_bit(imagen, i); //obtengo los 8 planos de 0 a 7 de la imagen
	}

	//empezar la reconstruccion: del 0 al 7
	CImg<unsigned char> resultado(planos[0]);
	CImgDisplay disp(resultado, "plano 0 = 0000 0001", 1); //es lo mismo que => planos[0]*pow(2,0);
	//int indice = 0;
	cout << endl << "Plano: " << plano<<endl;
	while (!disp.is_closed() && !disp.is_keyQ()) {
		disp.wait();
		if (disp.is_keyARROWUP() && plano<7) { //aumentar plano bits
			resultado += planos[++plano] * pow(2, plano); // ya esta incrementado! truquito...
		} else if (disp.is_keyARROWDOWN() && plano>0) {
			resultado -= planos[--plano] * pow(2, plano); // ya esta decrementado
		}
		disp.display(resultado);
		//disp.set_title((char *) plano);
		cout << endl << "Plano: " << plano<<endl;

	}

	return 0;
}
