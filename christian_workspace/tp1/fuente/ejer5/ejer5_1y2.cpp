//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

/*
 *submuestrear es lo mismo que reducir el tamanio por el factor
 *resize(50,50) es lo mismo que hacer lo otro??
 *resize(100,100) // no tiene efecto alguno sobre la imagen?????-???*/

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<int> imagen;
	imagen.load(
			"/home/christian/Documentos/universidad/2010/captura/imagenes/rmn.jpg");

	CImg<int> imagen_submuestreada(imagen); //submuestreo sucesivo con un factor de 2
	cout << "alto: " << imagen._width << "          ancho: " << imagen._height;

	const int factor = 2;
	imagen_submuestreada.resize((int) (imagen.width() / factor),
			(int) (imagen.height() / factor));

	//lo de arriba es lo mismo que hacer lo que esta aca abajo:

	//imagen_submuestreada.resize(50, 50).display();

	//resize(100,100) // no tiene efecto alguno sobre la imagen?????-???
	//resize(300,300)  //agranda a 300 x 300...
	//resize(50,50)  //la deja de 50 x 50 etc.

	CImgDisplay vent1(imagen, "imagen con parametro 1", 1), vent2(imagen,
			"imagen con parametro 0", 0),
			vent3(imagen, "imagen sin parametro"), vent4(imagen_submuestreada,
					"imagen con resize", 1);
	imagen_submuestreada.display("con el mismo factor que la anterior");
	while (!vent1.is_closed() && !vent2.is_closed() && !vent3.is_closed()
			&& !vent4.is_closed()) {
	}

	return 0;
}
