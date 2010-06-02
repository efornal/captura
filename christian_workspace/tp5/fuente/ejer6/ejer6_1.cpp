/*
 * ejer6_1.cpp
 *
 *  Created on: 16/05/2010
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

#include "../lib5/filtros.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f1", "../../imagenes/clown.jpg", "ruta archivo imagen" );
	const char
			*filename1 =
					cimg_option( "-f2", "../../imagenes/clown.jpg", "ruta archivo imagen" );
	CImg<float> img(filename); //imagen original
	CImg<float> img1(filename1);

	img.normalize(0, 255);
	img1.normalize(0, 255);

	CImgDisplay disporiginal(img, "imagen original");
	CImgDisplay disporiginal1(img1, "imagen original1");

	CImg<float> conv_img = img.get_convolve(img1);
	CImgDisplay esp(conv_img.get_FFT()[0].log(),
			"log(Real(fft(convolucion imagenes)))");
	//todo: esto no anda pero habria que probar igual ue comesta nada mas que en filtrar_desde_tiempo habria que hacerlo para quye
	//lo haga sin la magnitud y qu elo haga con fitlrar_complejo... y sacar la funcion de zeropaading (hacerla externa
	CImg<float> magH(2 * img.width(), 2 * img.height(), 1, 1);
	CImg<float> mul_frec_zeros = filtrar_desde_tiempo<float> (img, img1, magH);
	//CImgDisplay fil(magH, "Resp. en Frec. del filtro");
	CImgDisplay resul(mul_frec_zeros.log(), "filtrado frecuencial");
	while (!disporiginal.is_closed()) {
		disporiginal.wait();
	}
	return 0;
}

