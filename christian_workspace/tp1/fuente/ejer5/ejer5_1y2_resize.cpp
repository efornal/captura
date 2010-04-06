//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

/* El resize se puede coinciderar como un submuestreo, el tema es que dependiendo del tamanio de imagen
 * no necesariamente me va a estar sacando una fila y una columna cada un pixel...
 * resize(50,50) -> reduce en un 50% la imagen (es decir que la nueva va  a ser del 50% de la original en tamanio)
 * resize(100,100) -> no tiene efecto sobre la imagen
 * */

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<unsigned char> img1("../../imagenes/rmn.jpg");
	CImg<unsigned char> img2(img1);

	img2.resize((int) img1.width() / 2, (int) img1.height() / 2);
	CImg<unsigned char> img3(img2);
	img3.resize((int) img2.width() / 2, (int) img2.height() / 2);

	CImgDisplay vent1(img1, "Original", 0), vent2(img2, "resize a la mitad de la imagen 1", 1),
			vent3(img3, "resize a la mitad de la imagen 2", 1);
	while (!vent1.is_closed() && !vent2.is_closed()) {
	}
}
