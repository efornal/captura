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

	CImg<unsigned char> imagen("../../imagenes/clown.jpg");
	imagen.display("Pallazo antes del normalizado");
	imagen.normalize(imagen.min(), imagen.max()); //normalizo la imagen entre el valor minimo y maximo
	imagen.display("Pallazo despues del normalizado");
	//imagen.quantize(10); //cuantizo la imagen en 10 niveles de acuerdo a la cantidad de patrones
	imagen.display("Pallazo despues del normalizado y cuantizado");

	pasar_a_medios_tonos(imagen, 0).display("Modificando el tamanio");
	pasar_a_medios_tonos(imagen, 1).display("Resize");

	return 0;
}
