//============================================================================
// Name        : tp3.cpp
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main() {
	CImg<unsigned char> img;
	img.load("../../imagenes/camaleon.tif");

//	CImg<unsigned char> img_histograma = img.get_histogram(100);
	//CImg<unsigned char> img_ecualizada = img.get_equalize(100);
/*
	CImgDisplay disp1, disp1h, disp2, disp2h, disp3,disp3h;
	img_histograma.display(disp1);
	disp1.set_title("imagen original");*/

	return 0;
}
