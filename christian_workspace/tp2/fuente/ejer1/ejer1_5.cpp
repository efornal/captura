//FIXME: no entiendo el enunciado
//============================================================================
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include <string.h>

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> img(50, 50, 1, 1); //imagen binaria

	unsigned int valor = 0; //negro
	cimg_forXY(img, x,y)
		{
			img(x, y) = valor;
			valor = !valor;
		}

	img.normalize(0, 255); //imagen normalizada
	img.display();
	return 0;
}
