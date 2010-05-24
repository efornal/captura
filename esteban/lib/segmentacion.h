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


CImg<double> filtrado_prewitt( CImg<double> &img ) {
    return img.convolve( masks::prewitt_gx() ) +
        img.convolve( masks::prewitt_gy() ) +
        img.convolve( masks::prewitt_gxy() ) +
        img.convolve( masks::prewitt_gyx() );
}
