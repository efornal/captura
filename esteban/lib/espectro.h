/**
 * invariante a rotacion, dver prop fourier
*/
#include <CImg.h>
#include <string>
#include <vector>
#include <math.h>

#ifndef MAX_LINE_LENGTH
#include <CPDSI_functions.h>
#endif

using namespace std;
using namespace cimg_library;


CImg<double> fft_modulo( CImg<double> img, bool centrada=false ) {

    CImg<double> modulo( img.width(), img.height(), 1, 1, 0 );
    CImgList<double> tdf;
        
    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            modulo(i,j) = sqrt( pow( tdf[0](i,j), 2.0 ) +
                                pow( tdf[1](i,j), 2.0 ) ) +
                0.000001;
        }
    }

    if ( centrada ) { 
        //parametros de shift: x, y , z, v, border_condition
        modulo.shift( modulo.width()/2, modulo.height()/2, 0, 0, 2 );
    }

    return modulo;
}

CImg<double> fft_modulo_log( CImg<double> img, bool centrada=false ) {

    CImg<double> modulo( img.width(), img.height(), 1, 1, 0 );
    CImgList<double> tdf;
        
    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            modulo(i,j) = log( sqrt( pow( tdf[0](i,j), 2.0 ) +
                                     pow( tdf[1](i,j), 2.0 ) ) +
                               0.000001 );
        }
    }

    if ( centrada ) { 
        //parametros de shift: x, y , z, v, border_condition
        modulo.shift( modulo.width()/2, modulo.height()/2, 0, 0, 2 );
    }

    return modulo;
}
