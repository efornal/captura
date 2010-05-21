/*
 * ejer6_1.cpp
 *
 *  Created on: 13/05/2010
 *      Author: christian
 */

#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include "../lib6/restauracion.h"
#include "../../../tp5/fuente/lib5/lib5.h"
#include "../../../tp2/fuente/lib2/lut.h"
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/img_degradada.tif", "ruta archivo imagen" );
	CImg<double> img_degradada(filename); //imagen degradada

	CImg<double> img_degradada_fase = get_fase(img_degradada);
	CImg<double> img_degradada_magnitud = get_magnitud(img_degradada, true);
	CImgList<float> fft_imgdegra = img_degradada.get_FFT();


	CImgDisplay disp(img_degradada, "imagen degradada");

	CImgDisplay fase(img_degradada_fase, "fase de la FFT imagen degradada");
	CImgDisplay magnitudlog(img_degradada_magnitud.get_log(),
			"magn. de la FFT imagen degradada log");
	CImgDisplay magnitud(img_degradada_magnitud,
			"magn. de la FFT imagen degradada");
	img_degradada_magnitud.display();
	CImg<double> maximos = detectar_maximos(img_degradada_magnitud);

	//notch:
	CImgDisplay maxim(maximos, "maximos detectados de la FFT");
	maximos = negativo(maximos);

	CImgDisplay dispIMG_DEGRADADA(fft_imgdegra[0].get_log().get_normalize(0,
			255), "fft imagen degradada");

	//filtro el espectro....
	cimglist_for(fft_imgdegra, l) {
		cimg_forXY(fft_imgdegra[l], x,y)
			{
				fft_imgdegra[l](x, y) *= maximos(x, y);
			}
	}
	fft_imgdegra.get_FFT(true)[0].display();

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
