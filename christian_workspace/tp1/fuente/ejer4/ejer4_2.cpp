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

	imagen_norm.normalize(0, 255); //imagen normalizada

	CImgList<int> lista(imagen_norm, imagen_notnorm);
	CImgDisplay vent;
	vent.set_title("imagen normalizada e imagen sin normalizar respectivamente");
	lista.display(vent, true, 'y', 'c');

	imagen_norm.display("imagen normalizada entre 0 y 255");

	//imagen_notnorm.display("imagen sin normalizar");
	// en realidad no es sin normalizar ya que por defecto display normaliza la imagen

	while (!vent.is_closed()) {
	}
	return 0;
}
