/*
 * ejer1_1y2.cpp
 *
 *  Created on: 22/05/2010
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
#include "../lib7/CPDSI_segmentacion.h"

using namespace std;
using namespace cimg_library;
/*
 * http://users.cs.cf.ac.uk/Paul.Rosin/CM0311/dual2/hough.html
 * */
int main(int argc, char **argv) {
	CImg<double> img(500, 500, 1, 1, 0); //imagen original
	img(0, 0) = 1;
	img(0, 499) = 1;
	img(249, 249) = 1;
	img(0, 499) = 1;
	img(499, 499) = 1;
	img.normalize(0, 1);
	CImg<double> Hough = hough_directa(img);
	Hough.normalize(0, 1);
	CImg<double> inversa = hough_inversa(Hough);
	inversa.normalize(0, 1);
	img.normalize(0, 1);

	CImgDisplay disp(Hough, "Transf de Hough");
	CImgDisplay disp1(inversa, "inversa de Hough");
	CImgDisplay disp2(img, "imagen");

	while (!disp.is_closed()) {
		disp.wait();
	}
	return 0;
}
