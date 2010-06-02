#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C" {
#include "fftw3.h"
}
#endif

#include <iostream>
#include "../lib6/restauracion.h"

#include <CImg.h>

using namespace std;
using namespace cimg_library;

int main(int argc, char **argv) {
	const char
			*filename =
					cimg_option( "-f", "../../imagenes/parrot.tif", "ruta archivo imagen" );

	CImg<unsigned char> src(filename), dest(src, false),
			neighbor(5, 5); //Image definitions.
	typedef unsigned char uchar; // Avoid space in the second parameter of the macro CImg_5x5x1 below.
	CImg<> N(5, 5); // Define a 5x5 neighborhood as a 5x5 image.
	cimg_forC(src,k) // Standard loop on color channels
		cimg_for5x5(src,x,y,0,k,N,float) // 5x5 neighborhood loop.
				dest(x, y, k) = N.sum() / (5 * 5); // Averaging pixels to filter the color image.
	CImgList<unsigned char> visu(src, dest);
	visu.display("Original + Filtered"); // Display both original and filtered image.
	return 0;
}
