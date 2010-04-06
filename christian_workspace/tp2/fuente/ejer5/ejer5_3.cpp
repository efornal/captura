/*
 * ejer5_3.cpp
 *
 *  Created on: 06/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../lib/operadores_relacionales.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg <unsigned char> negro (255,255,1,1);
	negro.fill(0);

	CImg <unsigned char> blanco (255,255,1,1);
	blanco.fill(255);
//TODO: seguir con esto.. que no anda por ahora...
	menor(negro, blanco).normalize(0,255).display("menor(negro, blanco)");
	menor(blanco, negro).normalize(0,255).display("menor(negro, blanco)");
	menor_igual(negro, blanco).display("menor_igual(negro, blanco)");
	mayor(negro, blanco).display("mayor(negro, blanco)");
	mayor_igual(negro, blanco).display("mayor_igual(negro, blanco)");
	return 0;
}
