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
	CImg<int> imagen(256, 256, 1, 1);
	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = y;
		}
	int normalizado = 1;
	CImgDisplay ventana(imagen, "tonos de grises... columnas de 0 a 255",
			normalizado);//ojo si no lo normalizo no me pone tod en gris

	while (!ventana.is_closed()) {
	}
	return 0;
}
