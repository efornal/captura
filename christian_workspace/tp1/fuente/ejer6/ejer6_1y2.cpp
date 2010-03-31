//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

/*mayor nivel de cuantizacion mayor detalle.. fijarse en el punto .. el color...
 * igual que en muestreo :)
 * */
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<int>
			imagen(
					"../../imagenes/huang.jpg");
	// cuantizar la imagen desde 8 hasta 1 nivel/es

	CImgList<int> lista(imagen.get_quantize(1), imagen.get_quantize(2),
			imagen.get_quantize(3), imagen.get_quantize(4),
			imagen.get_quantize(5), imagen.get_quantize(6),
			imagen.get_quantize(7), imagen.get_quantize(8));
	lista.display("cuantizacion de 1 a 8 niveles");

	CImgDisplay vent1(imagen, "imagen original", 1);

	while (!vent1.is_closed()){}
	return 0;
}
