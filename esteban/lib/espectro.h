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
#include <complex>

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
 * Fase de la fft: atan(I/R)
 */
CImg<double> fft_fase( CImg<double> img, bool centrada=true ) {

    CImg<double> fase( img.width(), img.height(), 1, 1, 0 );
    CImgList<double> tdf;
    complex<double> I(0., 1.);
    complex<double> complejo = 0;

    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            complejo = tdf[0](i,j) + I*tdf[1](i,j);
            fase(i,j) = arg( complejo );
        }
    }

    return fase;
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
 * Retorna la imagen con espectro de solo fase (modulo = 1)
*/
CImg<double> a_solo_fase( CImg<double> img ) {

    CImg<double> fase( img.width(), img.height(), 1, 1, 0 );
    CImgList<double> tdf;
    complex<double> I(0., 1.);
    complex<double> complejo = 0;
    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            complejo = tdf[0](i,j) + I*tdf[1](i,j);
            fase(i,j) = arg( complejo );
            tdf[0](i,j) = cos(fase(i,j));
            tdf[1](i,j) = sin(fase(i,j));
        }
    }

    return tdf.get_FFT( true )[0]; //TDF inversa | solo parte real
}

/**
 * Retorna la imagen con espectro de solo modulo (fase = 0)
 */
CImg<double> a_solo_modulo( CImg<double> img ) {

    CImgList<double> tdf;

    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            tdf[0](i,j) = sqrt( pow( tdf[0](i,j), 2.0 ) +
                                pow( tdf[1](i,j), 2.0 ) ) +
                0.000001;
            
            tdf[1](i,j) = 0.0; // I=0
        }
    }

    return tdf.get_FFT(true)[0];     //TDF inversa | solo parte real
}

/**
 * Retorna la imagen cuyo espectro tiene la fase pasada por parametro
 * usado para formar imagen con fase de otra imagen
 */
CImg<double> a_fase_definida( CImg<double> img, CImg<double> fase ) {

    CImgList<double> tdf;

    tdf = img.get_FFT( false );  // lista: parte real e imag

    for (int i=0; i<img.width(); i++){
        for (int j=0; j<img.height(); j++) {
            tdf[1](i,j) = fase(i,j); // defino la fase
        }
    }

    return tdf.get_FFT(true)[0];     //TDF inversa | solo parte real
}
