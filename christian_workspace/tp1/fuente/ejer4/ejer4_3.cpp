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
	CImg<int> imagen_norm(100, 100, 1, 1, 0.5); //255 fondo blanco
	CImg<int> imagen_notnorm(100, 100, 1,1,255); //255 fondo blanco

	unsigned int valor=0;
	cimg_forXY(imagen_norm, x,y)
		{
			imagen_norm(x, y) = valor;
			imagen_notnorm(x, y) = valor;
			valor=!valor;
		}

	imagen_norm.normalize(0,255); //imagen normalizada

	CImgList<int> lista(imagen_norm, imagen_notnorm);
	CImgDisplay vent;
	lista.display(vent, false, 'y', 'c');

	imagen_norm.display("imagen normalizada entre 0 y 255");

	while (!vent.is_closed()) {
	}
	return 0;
}
