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
#include "../lib5/lib5.h"
#include "../lib5/figuras.h"
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"
#include "../../../tp3/fuente/lib3/mask.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", "ruta archivo imagen" );
	CImg<unsigned char> img(filename); //imagen original
	img.normalize(0,255);
	//circulo de altura 1 sobre una matriz de ceros:
	CImg<float> H(img.width(), img.height(), 1, 1);
	int radio = 10;
	circulo_centrado <float>(H.width()/2, H.height()/2, H, radio, 0); //creo la mascara
	H.normalize(0.0,1.0).display();
	CImgDisplay disp2;	H.display(disp2);
	CImgList <float> F = img.get_FFT();//obtengo la transformada
	CImg <float> F_real=F[0]; //parte real
	CImg <float> F_imag=F[1]; //parte imaginaria
	//filtrado
//multiplicar(F_real, H);

	H.shift( H.width()/2, H.height()/2, 0, 0, 2 );
	//F_real*=H;
	//F_imag*=H;
	cimg_forXY(F_real, x, y){
		F_real(x,y)*=H(x,y);
		F_imag(x,y)*=H(x,y);
	}
	F[0]=F_real;
	F[1]=F_imag;

	CImg <float> filtrada = F.get_FFT(true)[0];
	CImgDisplay disp1;
	filtrada.display(disp1);

	while (!disp1.is_closed()) {
		disp1.wait();
/*		if (disp1.wheel()){
			radio+=disp1.wheel();
			cout<<"Frec. Corte en: "<<radio<<endl;
		}

		filtrada.log().display(disp1);*/

	}
	return 0;
}
