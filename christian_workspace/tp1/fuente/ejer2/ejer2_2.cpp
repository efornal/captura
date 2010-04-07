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
	const char *filename = "../../imagenes/img.tif";
	CImg<unsigned char> imagen;
	imagen.load(filename);
	imagen.display("usando display"); //POSTA: cuando uso display esta normalizando y me tira info de lox pixels y demas

	CImgDisplay ventana(imagen, "imagen usando CImgDisplay ventana"); //POSTA: con CImgDisplay conserva el tamanio y no tira informacion alguna
	while (!ventana.is_closed()) {
	}

	return 0;
}
