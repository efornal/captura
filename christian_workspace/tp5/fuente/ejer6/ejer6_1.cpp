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
					cimg_option( "-f1", "../../imagenes/camaleon.tif", "ruta archivo imagen" );
	const char
			*filename1 =
					cimg_option( "-f2", "../../imagenes/clown.jpg", "ruta archivo imagen" );
	CImg<float> img(filename);
	CImg<float> img1(filename1);

	CImgDisplay disp(img, "imagen original");
	CImgDisplay disp1(img1, "imagen original 1");

	CImg<float> img_ceros(img.width() * 2.0 - 1.0, img.height() * 2.0 - 1.0, 1,
			1, 0.0); //relleno con ceros
	CImg<float> img1_ceros(img1.width() * 2.0 - 1.0, img1.height() * 2.0 - 1.0,
			1, 1, 0.0); //relleno con ceros
	cimg_forXY(img,x,y)
		{ //relleno con ceros las dos imagenes
			img_ceros(x, y) = img(x, y);
			img1_ceros(x, y) = img1(x, y);
		}
	CImgList<float> IMG_CEROS = img_ceros.get_FFT();
	CImgList<float> IMG_CEROS1 = img1_ceros.get_FFT();
	//multiplicarlas en frecuencia...
	cimg_forXY(IMG_CEROS[0],x,y)
		{
			IMG_CEROS[0](x,y)*=IMG_CEROS1[0](x,y);
			IMG_CEROS[1](x,y)*=IMG_CEROS1[1](x,y);
		} //multiplico en frecuencia las tdfs...
	CImgDisplay disp3(IMG_CEROS[0], "multplicacion en freuccnia de las dos imagenes...");
//fixme: preguntar lo del relleno con ceros como es...
	CImg<float> convolucion = img.get_convolve(img1);
	CImgList <float> CONVOLUCION = convolucion.get_FFT();
	CImgDisplay disp2(CONVOLUCION[0], "Real(fft(img, img1))");


	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
