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

	/* POSTA: Si la suma de la mascara es 0 elimina zonas homogeneas.. o sea no queda nada de bajos...
	 * Tener en cuenta que en las diapositivas hizo un clipping de los valores negativos! por eso aca se ven todas
	 * grises.. pero solo lo hizo para mostrar los bordes..
	 * */
	CImgDisplay disp1, disp2, disp3;
	imagen.display(disp1);
	disp1.set_title("imagen original");
	CImg<float> mascara1 = generar_mascara_PA_suma0<float>(1);
	CImg<float> mascara2 = generar_mascara_PA_suma0<float>(2);

	imagen.get_convolve(mascara1,1).display(disp2);
	disp2.set_title("mascara tipo 1 con suma 0");

	imagen.get_convolve(mascara2,1).normalize(0,255).display(disp3);
	disp3.set_title("mascara tipo 2 con suma 0");


	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
