//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================
//FIXME: ejecutar y  probar con las flechas lo que da varia rapidamente es por el factor nomas y como estoy trabjaando
//con imagenes unsgiend char me lo castea a entero?

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> imagen, im_pot;
	imagen.load("../../imagenes/rmn.jpg");
	CImgDisplay disp1, disp2;
	int i = 1;
	float factor = 1;
	im_pot = potencia<CImg<unsigned char> > (imagen, i, factor);
	disp1.set_title("grafica potencia variando el factor");
	im_pot.display(disp1);
	cout << "Factor: " << factor << endl;

	obtener_grafica_mapeo_potencia(i).display(disp2);

	while ((!disp1.is_closed() && !disp1.is_keyQ())) {
		disp1.wait();
		if (disp1.is_keyARROWDOWN())
			i = clipp(--i); // el i es el exponente
		else if (disp1.is_keyARROWUP()) {
			i = clipp(++i);
		} else if (disp1.is_keyARROWLEFT()) //factor
		{
			factor = clipp(--factor);
		} else if (disp1.is_keyARROWRIGHT()) {
			factor = clipp(++factor);
		}

		im_pot = potencia(imagen, i, factor);
		disp1.set_title("grafica logaritmo variando el factor");
		im_pot.display(disp1);
		cout << "exponenete: " << i
				<< "        - FACTOR: (original^i)*factor : " << factor << endl;
		obtener_grafica_mapeo_potencia(i).display(disp2);
	}
	return 0;
}
