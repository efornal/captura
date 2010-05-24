/*
 * hough_animada.cpp
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
	CImg<double> inversa = hough_inversa(img);
	inversa.normalize(0, 1);
	img.normalize(0, 1);

	CImgDisplay disp(Hough, "Transf de Hough");
	CImgDisplay disp1(inversa, "inversa de Hough");
	CImgDisplay disp2(img, "imagen");

	while (!disp2.is_closed()) {
		img.fill(0); //borro
		if ((disp2.mouse_x() >= 0 && disp2.mouse_x() <= 499) && (disp2.mouse_y()
				>= 0 || disp2.mouse_y() <= 499))
			img(disp2.mouse_x(), disp2.mouse_y()) = 1.0; //agrego punto
		img.normalize(0, 1); //normalizo.
		Hough = hough_directa(img);
		inversa = hough_inversa(img);
		img.display(disp2);
		disp2.set_title("imagen");
		Hough.display(disp);
		disp.set_title("transformada de hough");
		inversa.display(disp1);
		disp1.set_title("inversa de la transf de hough");
		disp2.wait();
	}
	return 0;
}
