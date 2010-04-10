/*
 * ejer7_2.cpp
 *
 *  Created on: 10/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"
#include "../lib/operadores_logicos.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	// se podria hacer tambien detectando o aplicando el mismo algoritmo
	// sobre solo una parte...

	// Tambien se podria tomar el valor del pixel en cierto lugar y si es uno u otro
	// ya sabes que placa es... variantes hay muchas...

	CImg<unsigned char> img_a7v600x, img_a7v600se;
	img_a7v600x.load("../../imagenes/a7v600-X.gif");
	img_a7v600se.load("../../imagenes/a7v600-SE.gif");

	CImgList<unsigned char> lista(img_a7v600x, img_a7v600se);
	lista.display("X y SE respectivamente");

	CImg<unsigned char> entrada_a7v600x(img_a7v600x);

	CImgList <unsigned char> result1(img_a7v600se, entrada_a7v600x);
	if (intensidades_iguales<CImg<unsigned char> > (img_a7v600se,
			entrada_a7v600x)){
		result1.display("son iguales");
	}
	else
		result1.display("son diferentes");

	CImgList <unsigned char> result2(img_a7v600x, entrada_a7v600x);
		if (intensidades_iguales<CImg<unsigned char> > (img_a7v600x,
				entrada_a7v600x)){
			result2.display("son iguales");
		}
		else
			result2.display("son diferentes");
	return 0;
}
