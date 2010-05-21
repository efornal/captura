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
#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
				*filename =
						cimg_option( "-f", "../../imagenes/pattern_libro.tif", "ruta archivo imagen" );
	CImg<unsigned char> img(filename); //imagen original
	/*Parameters: get_noise(sigma, type)
	 sigma Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global
	 value range.
	 noise_type Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper,
	 3=Poisson or 4=Rician).
	 * */
	double sigma = cimg_option("-sigma", 5.0 , "amplitud del ruido" );

	CImg<unsigned char> img_gaussian = img.get_noise(sigma, 0);
	CImg<unsigned char> img_uniform = img.get_noise(sigma, 1);
	CImg<unsigned char> img_saltpepper = img.get_noise(sigma, 2);
	CImg<unsigned char> img_rician = img.get_noise(sigma, 3);
	CImg<unsigned char> img_poisson = img.get_noise(sigma, 4);
	CImgDisplay disp1_h, disp2_h, disp3_h, disp4_h, disp5_h, dispo;

	CImgList<unsigned char> lista(img, img_gaussian, img_uniform,
			img_saltpepper, img_rician, img_poisson);

	CImgDisplay disp(lista,
			"original,gauss, uniform, saltpeeper, rician, poisson");

	img.normalize(0,255).get_histogram(256).display_graph(dispo, 3);
	dispo.set_title("histograma original");

	img_gaussian.get_histogram(256).display_graph(disp1_h, 3);
	disp1_h.set_title("ruido gaussiano");

	img_uniform.get_histogram(256).display_graph(disp2_h, 3);
	disp2_h.set_title("ruido uniforme");

	img_saltpepper.get_histogram(256).display_graph(disp3_h, 3);
	disp3_h.set_title("ruido salt-peeper");

	img_rician.get_histogram(256).display_graph(disp4_h, 3);
	disp4_h.set_title("ruido rician");

	img_poisson.get_histogram(256).display_graph(disp5_h, 3);
	disp5_h.set_title("ruido poisson");

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
