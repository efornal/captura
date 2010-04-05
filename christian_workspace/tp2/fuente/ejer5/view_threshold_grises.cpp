/*
 * view_threshold.cpp
 *
 *  Created on: 05/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> img1 = grises();
	CImg <unsigned char> mapeo(255,255,1,1);
	mapeo.fill(0);
	CImgDisplay disp, disp2, disp3;

	int cont = 0;

	img1.display(disp);
	disp.set_title("imagen");
	img1.get_threshold(0).normalize(0, 255).display(disp2);
	const char blanco[] ={255,255,255};
	mapeo.draw_graph(img1.get_threshold(0).normalize(0, 255), blanco, 1, 1, 1).display(disp3);

	while ((!disp.is_closed() && !disp.is_keyQ())) {
		disp.wait();
		cont=clipp(cont);
		if (disp.is_keyARROWDOWN()) {
			img1.get_threshold(cont--).normalize(0, 255).display(disp2);
			disp2.set_title("Aplicacion del threshold a la imagen");
			mapeo.fill(0);
			mapeo.draw_graph(img1.get_threshold(cont).normalize(0, 255), blanco, 1, 1, 1).display(disp3);
			disp3.set_title("grafica del threshold");
		} else if (disp.is_keyARROWUP()) {
			img1.get_threshold(cont++).normalize(0, 255).display(disp2);
			disp2.set_title("Aplicacion del threshold a la imagen");
			mapeo.fill(0);
			mapeo.draw_graph(img1.get_threshold(cont).normalize(0, 255), blanco, 1, 1, 1).display(disp3);
			disp3.set_title("grafica del threshold");
		}
		cout << "Threshold: " << cont << endl;
	}
	return 0;
}
