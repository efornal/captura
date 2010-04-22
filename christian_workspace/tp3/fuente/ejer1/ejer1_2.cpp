/*
 * ejer1_2.cpp
 *
 *  Created on: 16/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/* constrasTE: diferencia entre un punto y sus vecinos.. altos contraste cuando la diferencia es grande ->ecualizacion
	 * imA: medianamente buen contraste (al estar mas om enos dispersos), imagen mas oscura que clara
	 * imB: mal contraste, imagen clara (valores mas conecentrados a la derecha del histograma y estrechos)
	 * imC: buen contraste, imagen mas oscura que clara (valores disperos
	 * imD: medio contraste, imagen mas clara (valores mas conecentrados a la derecha en el histograma)
	 * imE: imagen bajo contraste, mas oscura (histograma conecentrado a la izquierda)
	 * */
	CImgDisplay disp1, disp2, disp3, disp4, disp5, disp_lista;
	CImg<float> imA, imB, imC, imD, imE;
	imA.load("../../imagenes/imagenA.tif");
	imB.load("../../imagenes/imagenB.tif");
	imC.load("../../imagenes/imagenC.tif");
	imD.load("../../imagenes/imagenD.tif");
	imE.load("../../imagenes/imagenE.tif");

	CImgList <float> lista (imA, imB, imC, imD, imE);
	lista.display(disp_lista);
	disp_lista.set_title("imA, imB, imC, imD, imE");

	imA.get_histogram(255).display_graph(disp1, 3);
	disp1.set_title("histograma imA");

	imB.get_histogram(255).display_graph(disp2, 3);
	disp2.set_title("histograma imB");

	imC.get_histogram(255).display_graph(disp3, 3);
	disp3.set_title("histograma imC");

	imD.get_histogram(255).display_graph(disp4, 3);
	disp4.set_title("histograma imD");

	imE.get_histogram(255).display_graph(disp5, 3);
	disp5.set_title("histograma imE");
	while (disp1.is_closed()) {
	}

	return 0;
}
