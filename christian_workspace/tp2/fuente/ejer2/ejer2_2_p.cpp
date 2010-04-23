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
	CImg<float> imagen, im_pot;
	imagen.load("../../imagenes/rmn.jpg");
	CImgDisplay disp1, disp2;
	float i = 1;
	float factor = 0.1;
	im_pot = potencia<CImg<float> > (imagen, i, factor);
	disp1.set_title("grafica potencia variando el factor");
	im_pot.display(disp1);
	cout << "Factor: " << factor << endl;
	obtener_grafica_mapeo_potencia< CImg<float> > (i).display(disp2);

	while ((!disp1.is_closed() && !disp1.is_keyQ())) {
		disp1.wait();
		if (disp1.is_keyARROWDOWN())
			i = clipp<float> (-0.1 + i); // el i es el exponente
		else if (disp1.is_keyARROWUP()) {
			i = clipp<float> (0.1 + i);
		} else if (disp1.is_keyARROWLEFT()) //factor
		{
			factor = clipp<float> (-0.1 + factor);
		} else if (disp1.is_keyARROWRIGHT()) {
			factor = clipp<float> (0.1 + factor);
		}

		im_pot = potencia(imagen, i, factor);
		disp1.set_title("grafica logaritmo variando el factor");
		im_pot.display(disp1);
		cout << "exponenete: " << i
				<< "        - FACTOR: (original^i)*factor : " << factor << endl;
		obtener_grafica_mapeo_potencia<CImg<float> > (i).display(disp2);
	}
	return 0;
}
