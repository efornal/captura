#include <stdlib.h>
#include <iostream>
#include "CImg.h"
using namespace cimg_library;
using namespace std;

CImg<> img("../../imagenes/bone.tif"), img2(img.width(), img.height(), 1, 1, 0);

int sX1 = 216, sY1 = 150;
float tolerancia = 50.0;
float intensidad = img(sX1, sY1);

int maxX = img.width(), maxY = img.height();

void recursion(int x, int y) {
	if (x > maxX || x < 0 || y > maxY || y < 0) {
		return;
	}
	if ((img(x, y) <= (intensidad + tolerancia) && img(x, y) >= (intensidad
			- tolerancia)) && img2(x, y) == 0) {
		img2(x, y) = 1;
		recursion(x + 1, y);
		recursion(x, y + 1);
		recursion(x - 1, y);
		recursion(x - 1, y - 1);
	} else
		return;
}

int main(int argc, char** argv) {

	img.channel(0);

	recursion(sX1, sY1);

	CImgDisplay vent1(img, "Original");
	CImgDisplay vent2(img2, "A ver que hicimos");

	while (!vent1.is_closed()) {
	}
	return (0);
}
