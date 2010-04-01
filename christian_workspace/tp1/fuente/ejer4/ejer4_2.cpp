//FIXME:
/*
 * cuando despliego las imagenes por separado parecen iguales aunque los valores no lo son
 * para que la matriz tome colores entre 0 y 255 si tiene valores de 100 x 100 hay que normalizarla?! conclusion
 * cuando los pongo en la lista se nota la diferencia .. que onda?
 * */
//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;


int main(int argc, char *argv[]) {
	CImg<int> imagen_norm(100, 100, 1, 1);
	CImg<int> imagen_notnorm(100, 100, 1, 1);

	cimg_forXY(imagen_norm, x,y)
		{
			imagen_norm(x, y) = y;
			imagen_notnorm(x, y) = y;
		}

	imagen_norm.normalize(0,255); //imagen normalizada

	CImgList<int> lista(imagen_norm, imagen_notnorm);
	CImgDisplay vent;
	lista.display(vent, true, 'y', 'c');

	imagen_norm.display("imagen normalizada entre 0 y 255");
	imagen_notnorm.display("imagen sin normalizar");

	while (!vent.is_closed()) {
	}
	return 0;
}
