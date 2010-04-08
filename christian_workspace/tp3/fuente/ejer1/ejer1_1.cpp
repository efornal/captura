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

	CImg<unsigned char> img_histograma = img.get_histogram(100);

	CImg<unsigned char> img_ecualizada = img.get_equalize(100);

	CImgDisplay disp1, disp2, disp3;
	img.display(disp1);
	disp1.set_title("original");

	//img_histograma.display_graph("histograma de imagen original", 3);
	//img_ecualizada.display_graph("ecualizacion de imagen original", 3);
	img_histograma.display_graph(disp2, 3);
	disp2.set_title("imagen de histograma");
	img_ecualizada.display_graph(disp3, 3);

	/*
	 img_histograma.display_graph(disp2, 3);
	 img_ecualizada.display_graph(disp3, 3);
	 cout << endl;
	 int levels = 1;
	 while (!disp1.is_closed() || disp1.is_keyQ()) {
	 if (disp1.is_keyARROWUP())
	 levels++;
	 else if (disp1.is_keyARROWDOWN() && levels > 1)
	 levels--;

	 img.get_histogram(levels).display_graph(disp2, 3);
	 img.get_equalize(levels).display_graph(disp3, 3);

	 cout << "Niveles de histograma: " << levels << endl;
	 }
	 */
	return 0;
}
