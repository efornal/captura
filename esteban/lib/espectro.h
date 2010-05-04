#define pdi_espectro 1
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#include <CImg.h>
#include <string>
#include <vector>
#include <math.h>

#ifndef MAX_LINE_LENGTH
#include <CPDSI_functions.h>
#endif

using namespace std;
using namespace cimg_library;


/**
   Modulo de la fft: |fft(f)|
   |fft(t)| = sqrt{ real^2 + imag^2 }
*/
CImg<double> fft_modulo( CImg<double> img, bool centrada=true ) {

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


/**
   Modulo de la fft con log aplicado: log{ |fft(f)| }
   |fft(t)| = sqrt{ real^2 + imag^2 }
   log{ |fft(f)| }
*/
CImg<double> fft_modulo_log( CImg<double> img, bool centrada=true ) {

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

/**
 *   Modulo de la fft , SIN LA FASE
 *   |fft(t)| = sqrt{ real^2 + imag^2 }
*/
CImg<double> fft_fase( CImg<double> img, bool centrada=true ) {

    CImg<double> fase( img.width(), img.height(), 1, 1, 0 );
    CImgList<double> tdf;
        
    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            fase(i,j) =  atan( tdf[1](i,j) / tdf[0](i,j) ) + 
                0.000001;
        }
    }

    if ( centrada ) { 
        //parametros de shift: x, y , z, v, border_condition
        fase.shift( fase.width()/2, fase.height()/2, 0, 0, 2 );
    }

    return fase;
}
