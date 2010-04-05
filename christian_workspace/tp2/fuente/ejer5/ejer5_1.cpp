/*
 * ejer5_1.cpp
 *
 *  Created on: 02/04/2010
 *      Author: christian
 */
#include <iostream>
#include <CImg.h>
#include "../ejer1/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> im1, im2;
	im1.load("../../imagenes/letras1.tif");
	im2.load("../../imagenes/letras2.tif");
	CImg<unsigned char> gris = grises();

	//convertir imagenes a binarias:
	CImg<unsigned char> im1_bin, im2_bin, im3_bin;
	im1_bin = get_binary(im1);
	im2_bin = get_binary(im2);
	im3_bin = get_binary(gris);

	//TODO: no funciona!!! porque con im2_bin.display() anda pero como esta aca abajo no!!!! :(
	CImgDisplay disp1, disp2, disp3, disp4, disp5, disp6;
	im2_bin.display(disp1);
	//disp1.set_title("Imagen 1");
	im1_bin.display(disp2);
//	disp2.set_title("Imagen 1 binaria");
	im2.display(disp3);
	disp3.set_title("Imagen 2");
	im2_bin.display(disp4);
	disp4.set_title("Imagen 2 binaria");
	gris.display(disp5);
	disp5.set_title("Imagen 3");
	im3_bin.display(disp6);
	disp6.set_title("Imagen 3 binaria");

	while (!disp1.is_closed()) {
	}
	/*//TODO: con listas no funciona!
	 CImgList <unsigned char> l(im1, im2, gris, im1_bin, im2_bin, im3_bin);
	 l.display("Originales y sus Imagenes binarias");*/
	/*
	 gris.get_threshold(128).display(); // FIXME: porque con el display solo anda y con la lista de abajo no??:
	 CImgList <unsigned char> lista(gris, gris.get_threshold(0), gris.get_threshold(128), gris.get_threshold(255));
	 lista.display("Escala de grises 0 a 255 - Aplicando threshold 0 - Aplicando threshold 128 - Aplicando threshold 255");
	 */
	return 0;
}
