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
	const char *filename =
			"/home/christian/Documentos/universidad/2010/captura/imagenes/huang.jpg";
	/*CImg<char>
	 original_image(
	 "/home/christian/Documentos/universidad/2010/captura/imagenes/huang.jpg"); //cargo imagen*/

	CImg <float> imagen(filename); //cargo la imagen
	imagen.channel(0); //canal 0
	imagen.display();
	CImg <float> imagenp(imagen); //creo una copia de la imagen original para recortarla
	imagenp.crop(37,14,55,32,true);


	CImgDisplay vent1(imagen, "original"), vent2(imagenp, "procesada");
	while (!vent1.is_closed()) {
		}

	//mostrar el rostro del camarografo:
	//CImgDisplay<char> ("")

	return 0;
}
