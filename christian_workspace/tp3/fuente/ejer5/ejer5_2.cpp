/*
 * ejer5_2.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	// filtros pasa altos
	CImg<float> imagen("../../imagenes/camaleon.tif");

	//FIXME: como que no funciona... hay que normalizar la mascara o como es el tema? porque el gris ese?
	/* supuestamente cuando la suma de la mascara es 0 elimina las zonas homogeneas
	 * */
	CImgDisplay disp1, disp2, disp3, disp4;
	imagen.display(disp1);
	disp1.set_title("imagen original");
	CImg<float> mascara1 = generar_mascara_PA_suma0<float>(1);
	CImg<float> mascara2 = generar_mascara_PA_suma0<float>(2);
	CImg<float> mascara3 = generar_mascara_PA_suma0<float>(3);

	imagen.get_convolve(mascara1).normalize(0,255).display(disp2);
	disp2.set_title("mascara tipo 1 con suma 0");

	imagen.get_convolve(mascara2).normalize(0,255).display(disp3);
	disp3.set_title("mascara tipo 2 con suma 0");

	imagen.get_convolve(mascara3).normalize(0,255).display(disp4);
	disp4.set_title("mascara tipo 3 con suma 0");

	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
