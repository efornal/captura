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
	CImg<double> img(512, 512, 1, 1, 0.0);
	CImg<double> img_rotada(512, 512, 1, 1, 0.0);
	linea_vertical(img, img.width() / 2.0, 0);

	img_rotada = img.get_rotate(20); //roto la imagen 20 grados....

	CImg<double> img_cortada = img.get_crop(176, 100, 432, 356);
	CImg<double> img_rotada_cortada = img_rotada.get_crop(176, 100, 432, 356);

	//visualizar las magnitudes de las imagenes...
	CImg<unsigned char> img_cortada_magnitud(256, 256, 1, 1);
	magn_tdf(img_cortada, img_cortada_magnitud, true);

	CImg<unsigned char> img_rotada_cortada_magnitud(256, 256, 1, 1);
	magn_tdf(img_rotada_cortada, img_rotada_cortada_magnitud, true);
	CImgList<double> lista1(img_cortada, img_cortada_magnitud);
	CImgList<double> lista2(img_rotada_cortada, img_rotada_cortada_magnitud);
	CImgDisplay disp1, disp2;
	lista1.display(disp1);
	disp1.set_title("imagen cortada y magnitud de su tdf");
	lista2.display(disp2);
	disp2.set_title("imagen rotadas cortada y magnitud de su tdf");
	/*

	 CImgDisplay disp3(img_cortada, "imagen cortada");
	 CImgDisplay disp4(img_cortada_magnitud, "magnitud de imagen cortada");
	 CImgDisplay disp5(img_rotada_cortada, "imagen rotada");
	 CImgDisplay disp6(img_rotada_cortada_magnitud,
	 "magnitud de la imagen rotada");
	 */
	/*fixme: conclusion!??? */
	while (!disp2.is_closed()) {
		disp2.wait();
	}
	return 0;
}
