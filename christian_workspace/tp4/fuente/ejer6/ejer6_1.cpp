/*
 * ejer6_1.cpp
 *
 *  Created on: 23/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/proc_color.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/* La segmentacion es un proceso que divide la imagen en regiones. Este ejercicio tiene por
	 * objetivo segmentar algun color en particular en una imagen en el modelo RGB
	 * Segmentacion en RGB. En este modelo se segmenta por el metodo de las rodajas de color con un
	 * modelo esferico. .*/
	//a---------------------------------------------------------------------------------------
	//cargue la imagen futbol.jpg
	CImg<float> imagen("../../imagenes/futbol.jpg");
	CImgDisplay disp1(imagen, "imagen de futbol", 0);
	//b---------------------------------------------------------------------------------------
	// tome una muestra representativa del color a segmentar y calcule el centro de la esfera
	// (valor medio de cada compoennete)
	while (!disp1.is_closed()) {
		disp1.wait();
	}

	return 0;
}
