//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main() {
	obtener_grafica_mapeo_potencia(2).display("Grafica Potencia");
	obtener_grafica_mapeo_logaritmo(15).display("Grafica Logaritmo");
	return 0;
}
