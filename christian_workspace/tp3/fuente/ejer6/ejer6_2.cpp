/*
 * ejer6_2.cpp
 *
 *  Created on: 17/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib3/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	/* Una forma de enfatizar alas altas frecuencias sin perder los detalles de la bajas
	 * frecuencias es el filtrado de alta pontencia: f_hb=A*f(x,y)-PB(f(x,y)) A>=1
	 * mayor A -> dejo mas vivas las bajas frecuencias
	 * */

	//filtrado por mascara difusa : f(x,y)- PB( f(x,y) )
	CImg<float> imagenc("../../imagenes/camaleon.tif");
	CImg<float> imagen1("../../imagenes/huang1.jpg");
	CImg<float> imagenh("../../imagenes/hand.tif");

	CImgDisplay disp1, disp2, disp3, disp4, disp5, disp6;

	CImgList<float> lista(imagenc, imagen1, imagenh);
	lista.display(disp1);
	disp1.set_title("imagenes originales - f(x,y)");

	CImg<float> resultadoc = imagenc.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());
	CImg<float> resultado1 = imagen1.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());
	CImg<float> resultadoh = imagenh.get_convolve(
			generar_mascara3x3_no_simetrica<float> ());

	CImgList<unsigned char> lista3(resultadoc, resultado1, resultadoh);
	lista3.display(disp3);
	disp3.set_title("PB(f(x,y))");

	CImgList<float> lista1(fil_high_boost<float> (imagenc,
			generar_mascara3x3_no_simetrica<float> ()).normalize(0, 255),
			fil_high_boost<float> (imagen1, generar_mascara3x3_no_simetrica<
					float> ()).normalize(0, 255),
			fil_high_boost<float> (imagenh, generar_mascara3x3_no_simetrica<
					float> ()).normalize(0, 255));
	lista1.display(disp2);
	disp2.set_title("filtro de Alta potencia - A*f(x,y)- PB(f(x,y)) con A=1");

	CImgList<float> lista2(fil_high_boost<float> (imagenc,
			generar_mascara3x3_no_simetrica<float> (), 3).normalize(0, 255),
			fil_high_boost<float> (imagen1, generar_mascara3x3_no_simetrica<
					float> (), 3).normalize(0, 255),
			fil_high_boost<float> (imagenh, generar_mascara3x3_no_simetrica<
					float> (), 3).normalize(0, 255));
	lista2.display(disp4);
	disp4.set_title("filtro de Alta potencia - A*f(x,y)- PB(f(x,y)) con A=3");

	CImgList<float> lista4(fil_high_boost<float> (imagenc,
			generar_mascara3x3_no_simetrica<float> (), 7).normalize(0, 255),
			fil_high_boost<float> (imagen1, generar_mascara3x3_no_simetrica<
					float> (), 7).normalize(0, 255),
			fil_high_boost<float> (imagenh, generar_mascara3x3_no_simetrica<
					float> (), 7).normalize(0, 255));
	lista4.display(disp5);
	disp5.set_title("filtro de Alta potencia - A*f(x,y)- PB(f(x,y)) con A=7");

	CImgDisplay dispnew;
	CImgList<float> lista1solapasada(fil_high_boost_1solapasada<float> (
			imagenc, 7.0, 2).normalize(0,255), fil_high_boost_1solapasada<float> (imagenc, 3.0,
			1).normalize(0,255));
	lista1solapasada.display(dispnew);
	dispnew.set_title(
			"filtrada con una sola pasada, mascara tipo 1 y tipo 2 respectivamente");

	CImgList<float> lista5(fil_high_boost<float> (imagenc,
			generar_mascara3x3_no_simetrica<float> (), 10).normalize(0, 255),
			fil_high_boost<float> (imagen1, generar_mascara3x3_no_simetrica<
					float> (), 10).normalize(0, 255),
			fil_high_boost<float> (imagenh, generar_mascara3x3_no_simetrica<
					float> (), 10).normalize(0, 255));
	lista5.display(disp6);
	disp6.set_title("filtro de Alta potencia - A*f(x,y)- PB(f(x,y)) con A=10");
	while (!disp1.is_closed()) {
	}
	return 0;
}
