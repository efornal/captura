/**
 * POSTA: a todos los filtrados (al menos en segmentacion)
 * le aplicamos abs(), es la forma correcta de verlos.
*/

#define pdi_segmentacion 1
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#ifndef MAX_LINE_LENGTH
#include <CPDSI_functions.h>
#endif

#include <masks.h>

using namespace std;
using namespace cimg_library;


CImg<double> filtrado_roberts( CImg<double> img ) {
    return 
        img.get_convolve( masks::roberts_gx() ).abs() +
        img.get_convolve( masks::roberts_gy() ).abs();
}

CImg<double> filtrado_prewitt( CImg<double> img ) {
    return 
        img.get_convolve( masks::prewitt_gx() ).abs() +
        img.get_convolve( masks::prewitt_gy() ).abs() +
        img.get_convolve( masks::prewitt_gxy() ).abs() +
        img.get_convolve( masks::prewitt_gyx() ).abs();
}

CImg<double> filtrado_sobel( CImg<double> img ) {
    return 
        img.get_convolve( masks::sobel_gx() ).abs() +
        img.get_convolve( masks::sobel_gy() ).abs() +
        img.get_convolve( masks::sobel_gxy() ).abs() +
        img.get_convolve( masks::sobel_gyx() ).abs();
}

CImg<double> filtrado_laplaciano_g( CImg<double> img ) {
    return img.get_convolve( masks::laplaciano_g() ).abs();
}
