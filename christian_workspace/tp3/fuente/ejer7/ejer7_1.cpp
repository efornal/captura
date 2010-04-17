/*
 * ejer7_1.cpp
 *
 *  Created on: 08/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/*TODO: calcular el histograma y solo aplicar al valor del centro...
	 * tomar imagen vecindad como una nueva imagen.. . cortamos ese pedazo le  hcemos la imagen ecualizada... tomamos le valor delo medio
	 * y reemplazamos la imagen por eso... y asi sucesivamente
	 *
	 * */
	CImg<unsigned char> imagen("../../imagenes/ej7a.tif");
	CImgDisplay disp1, disp2, disp3;
	int nlevels = 255;
	CImg<unsigned char> imagen_ecualizada = imagen.get_equalize(nlevels);

	CImg<unsigned char> aux(3, 3, 0, 0); //creo una copia de la imagen original
	CImg<unsigned char> aux1(imagen); //creo una copia de la imagen original
//FIXME: no me anda el tema de l mascara....
	cimg_for3x3(aux1, x, y, 0, 0, 0)
		{
			aux(x,y)=aux1(x,y).get_equalize(nlevels)(1,1);
		}
	CImgList<unsigned char> lista(imagen, imagen_ecualizada, aux1);
	lista.display(disp1);
	disp1.set_title(
			"imagen original - imagen ecualizada - imagen ecualizada por zonas");

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
