/*
 * ejer5_1_a.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	//parte b - ecualizar cada componente por separado
		CImg<float> imagen_oscura_R_equalizada(imagen_oscura_R),
				imagen_oscura_G_equalizada(imagen_oscura_G),
				imagen_oscura_B_equalizada(imagen_oscura_B);

		imagen_oscura_R_equalizada.equalize(255);
		cout << "spectrum: " << imagen_oscura_R_equalizada.spectrum();
		imagen_oscura_G_equalizada.equalize(255);
		imagen_oscura_B_equalizada.equalize(255);
		CImg<float> imagen_oscura_ecualizada_intependiente = componer_imagen<CImg<
				float> > (imagen_oscura_R_equalizada, imagen_oscura_R_equalizada,
				imagen_oscura_R_equalizada);
		CImg<float> imagen_oscura_ecualizada_global = imagen_oscura.get_equalize(
				255);
return 0;
}
