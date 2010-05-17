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

	CImg<unsigned char> img(256, 256, 1, 1); //imagen original
	/*Parameters: get_noise(sigma, type)
	 sigma Amplitude of the random additive noise. If sigma<0, it stands for a percentage of the global
	 value range.
	 noise_type Type of additive noise (can be 0=gaussian, 1=uniform, 2=Salt and Pepper,
	 3=Poisson or 4=Rician).
	 * */
	float sigma=5.0;
	img.fill(128);
	CImg<unsigned char> img_gaussian = img.get_noise(sigma, 0);
	CImg<unsigned char> img_uniform = img.get_noise(sigma, 1);
	CImg<unsigned char> img_saltpepper = img.get_noise(sigma, 2);
	CImg<unsigned char> img_rician = img.get_noise(sigma, 3);
	CImg<unsigned char> img_poisson = img.get_noise(sigma, 4);
	CImgDisplay disp1_h, disp2_h, disp3_h, disp4_h, disp5_h, dispo;

	CImgDisplay dis(img, "imagen original");
	img.normalize(0,255).get_histogram(255).display_graph(dispo, 3);
	dispo.set_title("histograma original");

	CImgDisplay disp(img_gaussian, "ruido gaussiano");
	img_gaussian.get_histogram(256).display_graph(disp1_h, 3);
	disp1_h.set_title("ruido gaussiano");

	CImgDisplay disp1(img_uniform, "ruido uniforme");
	img_uniform.get_histogram(256).display_graph(disp2_h, 3);
	disp2_h.set_title("ruido uniforme");

	CImgDisplay disp2(img_saltpepper, "salt & pepper");
	img_saltpepper.get_histogram(256).display_graph(disp3_h, 3);
	disp3_h.set_title("ruido salt-peeper");

	CImgDisplay disp3(img_rician, "rician");
	img_rician.get_histogram(256).display_graph(disp4_h, 3);
	disp4_h.set_title("ruido rician");

	CImgDisplay disp4(img_poisson, "poisson");
	img_poisson.get_histogram(256).display_graph(disp5_h, 3);
	disp5_h.set_title("ruido poisson");

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
