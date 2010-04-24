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
	CImg<double> imagen0(300, 300, 1, 1);
	CImg<double> imagen1(300, 300, 1, 1);
	CImg<unsigned char> mod_0(300, 300, 1, 1);
	CImg<unsigned char> mod_1(300, 300, 1, 1);
	CImg<double> imagen2(300, 300, 1, 1);
	CImg<unsigned char> mod_2(300, 300, 1, 1);
	CImg<double> imagen3(300, 300, 1, 1);
	CImg<unsigned char> mod_3(300, 300, 1, 1);
	float radio = 50.0;
	int posx=imagen0.width()/2;
	int posy=imagen0.height()/2;
	circulo_centrado(posx, posy, imagen0, radio);
	cuadrado_centrado(imagen1, 30, 30);
	linea_vertical(imagen2, imagen2.width() / 2);
	linea_horizontal(imagen3, imagen3.height() / 3);

	magn_tdf(imagen0, mod_0, 1);
	CImgDisplay disp1, disp1_1;
	imagen0.display(disp1);
	mod_0.display(disp1_1);

	magn_tdf(imagen1, mod_1, 1);
	magn_tdf(imagen2, mod_2, 1);
	magn_tdf(imagen3, mod_3, 1);

	CImgList<double> lista1(imagen1, mod_1);
	CImgList<double> lista2(imagen2, mod_2);
	CImgList<double> lista3(imagen3, mod_3);

	CImgDisplay disp2(lista1, "imagen y su transformada");
	CImgDisplay disp3(lista2, "imagen y su transformada");
	CImgDisplay disp4(lista3, "imagen y su transformada");
	/*CImg<unsigned char> modulo;
	 magn_tdf(imagen, modulo, 1); //transformada con la funcion de la catedra
	 CImgDisplay disp2(modulo, "modulo de la imagen", 0);*/
	while (!disp1.is_closed()) {

		if (disp1.is_keyPAGEUP()) {//crecer radio
			radio++;
			cout<<"radio: "<<radio<<endl;
		} else if (disp1.is_keyPAGEDOWN()) {
			//decrece radio
			radio-=1.0;
			cout<<"radio: "<<radio<<endl;
		} else if (disp1.is_keyARROWRIGHT()){
			posx++;
		} else if (disp1.is_keyARROWLEFT()){
			posx--;
		} else if (disp1.is_keyARROWUP()){
			posy--;
		} else if (disp1.is_keyARROWDOWN()){
			posy++;
		}
		//mostrar
		circulo_centrado(posx, posy, imagen0, radio);
		magn_tdf(imagen0, mod_0, 1);
		imagen0.display(disp1);
		mod_0.display(disp1_1);
	}
	return 0;
}
