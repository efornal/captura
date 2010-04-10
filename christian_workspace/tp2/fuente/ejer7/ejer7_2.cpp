/*
 * ejer7_2.cpp
 *
 *  Created on: 10/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg < unsigned char > img_a7v600x, img_a7v600se;
	img_a7v600x.load("a7v600-X.gif");
	img_a7v600se.load("a7v600-SE.gif");
	img_a7v600se.display("se");
	img_a7v600x.display("x");

	//binarizo la imagen, hago un and entre ambas y si me da 1 siginifica que son iguales

	CImg < unsigned char > img_entrada1, img_entrada2; // es la imagen la cual supongo no voy a saber cual es..
	/*img_entrada1 (img_a7v600x);
	img_entrada2 (img_a7v600se);*/





return 0;
}
