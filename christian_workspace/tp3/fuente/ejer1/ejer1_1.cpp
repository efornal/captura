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
	int n=100;
	CImg<unsigned char> img_histograma = img.get_histogram(n); // me agrupa los valores cada 9.8 -> (25*100)/100
	CImg<unsigned char> img_ecualizada = img.get_equalize(n);
	CImg<unsigned char> img_histo_ecua = img_ecualizada.get_histogram(n);

	CImgDisplay disp1, disp1h, disp2, disp2h;

	img.display(disp1); //muestro imagen original
	disp1.set_title("imagen original");

	img_ecualizada.display(disp2); //muestro imagen ecualizada
	disp2.set_title("imagen ecualizada");

	img_histograma.display_graph(disp1h, 3); //muestro histograma original
	disp1h.set_title("histograma imagen original");

	img_histo_ecua.display_graph(disp2h, 3); //muestro histograma ecualizada
	disp2h.set_title("histograma de imagen ecualizada");

	while (!disp1.is_closed()) {
		disp1.wait();
	}

	return 0;
}
