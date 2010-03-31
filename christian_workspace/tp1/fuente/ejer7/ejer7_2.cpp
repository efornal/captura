//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================


//http://usuarios.multimania.es/explorar/halfto/halfto.htm
#include <CImg.h>
#include <iostream>
#include "med_ton.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

	CImg<unsigned char> imagen(256, 256, 1, 1);
	cimg_forXY(imagen, x,y)
		{
			imagen(x, y) = y;
		}
	int normalizado = 1;
	CImgDisplay ventana(imagen, "tonos de grises... columnas de 0 a 255", normalizado);
	CImgDisplay ventana1(pasar_a_medios_tonos(imagen, 0), "Modificando el tamanio", normalizado);
	CImgDisplay ventana2(pasar_a_medios_tonos(imagen, 1), "Sin modificar tamanio", normalizado); // que esta pasando aca??

	while (!ventana.is_closed()&&!ventana1.is_closed()&&!ventana2.is_closed()) {
	}
	return 0;
}
