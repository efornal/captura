/*
 * ejer7_3.cpp
 *
 *  Created on: 11/04/2010
 *      Author: christian
 */

#include <iostream>
#include <CImg.h>
#include "../lib/lib.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {

	CImg<unsigned char> limpia_img_a7v600x, limpia_img_a7v600se;
	limpia_img_a7v600x.load("../../imagenes/a7v600-X.gif");
	limpia_img_a7v600se.load("../../imagenes/a7v600-SE.gif");

	CImg<unsigned char> a_identificar_img_a7v600x, a_identificar_img_a7v600se;
	a_identificar_img_a7v600x.load("../../imagenes/a7v600-X(RImpulsivo).gif");
	a_identificar_img_a7v600se.load("../../imagenes/a7v600-SE(RImpulsivo).gif");

	int cantidad_cuadros = 1000; //cantidad de cuadros a promediar
	double varianza = 15; //varianza del ruido

	CImg<unsigned char> ensuciada_img_a7v600x[cantidad_cuadros];
	CImg<unsigned char> ensuciada_img_a7v600se[cantidad_cuadros];

	for (int i = 0; i < cantidad_cuadros; i++) {
		ensuciada_img_a7v600x[i] = limpia_img_a7v600x.get_noise(varianza, 2);
		ensuciada_img_a7v600se[i] = limpia_img_a7v600se.get_noise(varianza, 2);
	}

	CImg<float> reconst_img_a7v600x = ensuciada_img_a7v600x[0];
	CImg<float> reconst_img_a7v600se = ensuciada_img_a7v600se[0];
	for (int i = 1; i < cantidad_cuadros; i++) {
		reconst_img_a7v600x = sumar<CImg<float> > (reconst_img_a7v600x,
				ensuciada_img_a7v600x[i]);
		reconst_img_a7v600se = sumar<CImg<float> > (reconst_img_a7v600se,
				ensuciada_img_a7v600se[i]);
	}

	cimg_forXY(reconst_img_a7v600x, x, y)
		{
			reconst_img_a7v600x(x, y) /= cantidad_cuadros;
			reconst_img_a7v600se(x, y) /= cantidad_cuadros;
		}

	CImgList<unsigned char> originales(limpia_img_a7v600x, limpia_img_a7v600se);
	originales.display("Originales limpias, x y se respectivamente");

	CImgList<unsigned char> a_identificar(a_identificar_img_a7v600x,
			a_identificar_img_a7v600se);
	a_identificar.display(
			"Imagenes a mejorar e identificar X y SE respectivamente");





	ensuciada_img_a7v600se[10].display("ensuciadas por mi");
	/*CImgList<unsigned char> sucias(ensuciada_img_a7v600x[10],
			ensuciada_img_a7v600se[10]);
	sucias.display("limpias contaminadas manualmente, x y se respectivamente");*/




/*	//TODO:
	CImgList<unsigned char> reconstruidas(reconst_img_a7v600x,
			reconst_img_a7v600se);
	reconstruidas.display("reconstruidas, x y se respectivamente");*/

	CImgDisplay dispaux;
	reconst_img_a7v600x.display(dispaux);
	dispaux.set_title("reconstruida x");

	while (!dispaux.is_closed()){}
	return 0;
}
