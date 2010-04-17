/*
 * ejer6_1.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	//filtrado por mascara difusa : f(x,y)- PB( f(x,y) )
	CImg<float> imagenc("../../imagenes/camaleon.tif");
	CImg<float> imagen1("../../imagenes/huang1.jpg");
	CImg<float> imagenh("../../imagenes/hand.tif");

	CImgDisplay disp1, disp2, disp3;

	CImgList<float> lista(imagenc, imagen1, imagenh);
	lista.display(disp1);
	disp1.set_title("imagenes originales - f(x,y)");

	CImg<float> resultadoc = imagenc.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());
	CImg<float> resultado1 = imagen1.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());
	CImg<float> resultadoh = imagenh.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());

	CImgList<float> lista3(resultadoc, resultado1, resultadoh);
	lista3.display(disp3);
	disp3.set_title("PB(f(x,y))");

	CImgList<float>
			lista1(fil_masc_difusa <float> (imagenc, generar_mascara3x3_no_simetrica<
					float> ()), fil_masc_difusa <float> (imagen1,
					generar_mascara3x3_no_simetrica<float> ()),
					fil_masc_difusa <float> (imagenh, generar_mascara3x3_no_simetrica<
							float> ()));
	lista1.display(disp2);
	disp2.set_title("filtro de mascara difusa - f(x,y)- PB(f(x,y))");
	while (!disp1.is_closed()) {
	}
	return 0;
}
