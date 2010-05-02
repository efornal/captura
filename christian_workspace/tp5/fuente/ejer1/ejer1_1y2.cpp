/*
 * ejer1_2.cpp
 *
 *  Created on: 22/04/2010
 *      Author: christian
 */
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include <CImg.h>
#include "../lib/lib5.h"
#include "../../../tp4/fuente/lib/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	cout << "USE: " << endl
			<< "rueda del mouse para aumentar o disminuir tamaños" << endl
			<< "      R->rectangulo," << endl << "      C->circulo," << endl
			<< "      H->Linea Horizontal," << endl
			<< "      V->Linea Vertical," << endl;
	CImg<double> imagen0(300, 300, 1, 1);
	CImg<unsigned char> mod_0_centrada(300, 300, 1, 1);
	CImg<unsigned char> mod_0_nocentrada(300, 300, 1, 1);
	CImg<double> fase0(300, 300, 1, 1);
	//FIXME: ver cuadrado y fases de las lineas.. estara bien?
	float radio = 50.0;
	int posx = imagen0.width() / 2;
	int posy = imagen0.height() / 2;

	circulo_centrado(posx, posy, imagen0, radio);

	magn_tdf(imagen0, mod_0_centrada, 1);
	magn_tdf(imagen0, mod_0_nocentrada, 0);

	int dimx = 50;
	int dimy = 50;
	float angulo=0.0;
	fase0 = get_fase(imagen0);
	CImgDisplay disp1;
	fase0.display(disp1);
	CImgDisplay disp0;
	CImgList<double> lista0(imagen0, mod_0_centrada, mod_0_nocentrada);
	lista0.display(disp0);
	bool c = true; //circulo
	bool h = false; //linea horizontal
	bool v = false; // linea vertical
	bool r = false; //linea rectangular
	while (!disp0.is_closed()) {
		if (disp0.is_keyC()) {
			c = true; //circulo
			h = false; //linea horizontal
			v = false; // linea vertical
			r = false; //linea rectangular
			angulo=0.0;
		} else if (disp0.is_keyH()) {
			c = false; //circulo
			h = true; //linea horizontal
			v = false; // linea vertical
			r = false; //linea rectangular
			angulo=0.0;
		} else if (disp0.is_keyV()) {
			c = false; //circulo
			h = false; //linea horizontal
			v = true; // linea vertical
			r = false; //linea rectangular
			angulo=0.0;
		} else if (disp0.is_keyR()) {
			c = false; //circulo
			h = false; //linea horizontal
			v = false; // linea vertical
			r = true; //linea rectangular
			angulo=0.0;
		}
		if (disp0.is_keySHIFTLEFT()){
			//rotar en sentido antihorario.
			angulo--;
		}
		if (disp0.is_keySHIFTRIGHT()) {
			//rotar en sentido horario.
			angulo++;

		}
		if (disp0.is_keyY()){
			dimy++;
		}
		if (disp0.is_keyH()){
			dimy--;
		}
		if (c) { //circulo
			circulo_centrado(disp0.mouse_x(), disp0.mouse_y(), imagen0, radio
					+ disp0.wheel(), angulo);
			cout << "Radio del circulo: " << radio + disp0.wheel() << endl;
		} else if (h) { //linea horizontal
			linea_horizontal<double> (imagen0, disp0.mouse_y(), angulo);
		} else if (v) { //linea vertical
			linea_vertical(imagen0, disp0.mouse_x(), angulo);
		} else if (r) { //rectangulo
			cuadrado_centrado(imagen0, dimx + disp0.wheel(), dimy, disp0.mouse_x(), disp0.mouse_y(), angulo);
			cout << "Cuadrado: " << dimx + disp0.wheel() << endl;
		}
		lista0.clear();
		magn_tdf(imagen0, mod_0_centrada, 1);
		magn_tdf(imagen0, mod_0_nocentrada, 0);
		fase0 = get_fase(imagen0);

		lista0.insert(imagen0);
		lista0.insert(mod_0_centrada);
		lista0.insert(mod_0_nocentrada);
		fase0.display(disp1);
		disp1.set_title("fase");
		lista0.display(disp0);

		disp0.set_title(
				"imagen original, magnitu centrada, magnitud no centrada");
	}
	return 0;
}
