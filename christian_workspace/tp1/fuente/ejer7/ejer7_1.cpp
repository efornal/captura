//TODO: Ver la funcion el tema cuando hago la asignacion que deja los bordes mal como solucuionarlo..

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
	/*POSTA: al hacer el resize se ve mal porque estoy reduciendo el tamanio a 3 veces por tanto los patrones que eran
	 * un simil gris pasan a ser negro.. obtengo como resultado una imagen binaria solo negros y blancos
	 * */

	return 0;
}
