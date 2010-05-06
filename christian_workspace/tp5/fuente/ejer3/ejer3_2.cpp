/*
 * ejer3_2.cpp
 *
 *  Created on: 05/05/2010
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
#include "../../../tp3/fuente/lib/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<unsigned char> img("../../imagenes/huang2.jpg"); //imagen original
	//circulo de altura 1 sobre una matriz de ceros:
	CImg<float> H(img.width(), img.height(), 1, 1);
	int radio = 50;
	circulo_centrado <float>(H.width()/2, H.height()/2, H, radio, 0); //creo la mascara
	H.normalize(0.0,1.0).display();
	CImgDisplay disp2;
	H.display(disp2);
	CImgList <float> F = img.get_FFT();//obtengo la transformada
	CImg <float> F_real=F[0]; //parte real
	CImg <float> F_imag=F[1]; //parte imaginaria
	//filtrado

	F_real*=H;
	F_imag*=H;
	F[0]=F_real;
	F[1]=F_imag;
	CImg <float> filtrada = F.get_FFT(true)[0];
	CImgDisplay disp1;
	filtrada.log().normalize(0,255).display(disp1);

	while (!disp1.is_closed()) {
		disp1.wait();
	}
	return 0;
}
