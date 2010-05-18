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
#include <complex>
using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char *filename = cimg_option( "-f", "../../imagenes/avion.jpg",
	                                        "ruta archivo imagen" );
	const char *filename1 = cimg_option( "-i", "../../imagenes/aeropuerto.jpg",
		                                        "ruta archivo imagen2" );
	CImg<double> img(filename); //imagen original
	//TODO:
	CImg<double> img_aeropuerto(filename1);
	CImgList<double> lista_imagenes(img, img_aeropuerto);
	CImgDisplay displis1(lista_imagenes);
	displis1.set_title("Imagenes originales");

	CImg<double> img_fase = get_fase<double> (img); //obtengo fase de la fft
	CImg<double> img_magnitud = get_magnitud<double> (img);
	CImg<double> img_fase_aeropuerto = get_fase<double> (img_aeropuerto); //obtengo fase de la fft
	CImg<double> img_magnitud_aeropuerto =
			get_magnitud<double> (img_aeropuerto);

	//construir imagen con fase de img y magnitud de img_aeropuerto.
	CImgList<double> img_recons1 = img.get_FFT(); // todo: habria que crearla vacia...

	cimg_forXY(img_fase, x, y)
		{
			img_recons1[0](x, y) = img_magnitud_aeropuerto(x, y)*cos(img_fase_aeropuerto(x,y));
			img_recons1[1](x, y) = img_magnitud(x, y)*img_fase(x, y);
		}

	CImg <double> imagenaa=img_recons1.get_FFT(true)[0];
	CImgDisplay dis(imagenaa, "");

	while (!displis1.is_closed()) {
		displis1.wait();
	}
	return 0;
}
