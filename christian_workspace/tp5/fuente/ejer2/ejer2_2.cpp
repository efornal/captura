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
#include "../lib5/lib5.h"
#include "../lib5/figuras.h"
#include "../../../tp4/fuente/lib4/CPDSI_functions.h"

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	CImg<double> img("../../imagenes/avion.jpg"); //imagen original
	CImg<double> img_aeropuerto("../../imagenes/aeropuerto.jpg");
	CImgList<double> lista_imagenes(img, img_aeropuerto);
	CImgDisplay displis1(lista_imagenes);
	displis1.set_title("Imagenes originales");

	CImg<double> img_fase = get_fase<double> (img); //obtengo fase de la fft
	CImg<double> img_magnitud = get_magnitud<double> (img);
	CImg<double> img_fase_aeropuerto = get_fase<double> (img_aeropuerto); //obtengo fase de la fft
	CImg<double> img_magnitud_aeropuerto =
			get_magnitud<double> (img_aeropuerto);

	//construir imagen con fase de img y magnitud de img_aeropuerto.
	CImgList<double> img_recons1 = img.get_FFT(); // fixme: no se como crearla vacia!!!

	cimg_forXY(img_fase, x, y)
		{
			img_recons1[0](x, y) = img_magnitud_aeropuerto(x, y);
			img_recons1[1](x, y) = img_fase(x, y);
		}
	/*cimglist_apply(img_recons1, shift)
	 (img.width() / 2, img.height() / 2, 0, 0, 2);
	 */
	CImg <double> imagenaa=img_recons1.get_FFT(true)[0];
	imagenaa.log().normalize(0,255).display();

	while (!displis1.is_closed()) {
		displis1.wait();
	}
	return 0;
}
