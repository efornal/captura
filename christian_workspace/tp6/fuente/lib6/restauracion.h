/*
 * filtros.h
 *
 *  Created on: 16/05/2010
 *      Author: christian
 */

#include <CImg.h>
using namespace std;
using namespace cimg_library;


// ==========================================================
//                        ruido
// ==========================================================
/*
 * noice: Add random noise to the values of the instance image.
 *
 * Parameters:
 *   - sigma      Amplitude of the random additive noise.
 *                If sigma<0, it stands for a percentage of the global value range.
 *
 *   - noise_type Type of additive noise
 *                0 = gaussian,
 *                1 = uniform,
 *                2 = Salt and Pepper,
 *                3 = Poisson
 *                4 = Rician
 */
template <class T>
void gen_ruido_gaussiano( CImg<T> &img, double sigma ) {
	/**
	 * Genera ruido gausiano en la imagen dada
	 */
    img.noise( sigma, 0); // gaussian = 0
}

template <class T>
void gen_ruido_uniforme( CImg<T> &img, double sigma ) {
	/**
	 * Genera ruido uniforme en la imagen dada
	 */
    img.noise( sigma, 1);
}

template <class T>
void gen_ruido_sal_y_pimienta( CImg<T> &img, double sigma ) {
	/**
	 * Genera ruido sal y pimienta en la imagen dada
	 */
    img.noise( sigma, 2);
}

template <class T>
void gen_ruido_sal( CImg<T> &img, double sigma ) {
	/**
	 * Genera ruido sal (unicamente) en la imagen dada
	 */
    CImg<T> ruido ( img.width(), img.height(),1,1,0);
    ruido.noise( sigma, 2);
    cimg_forXY(img,x,y){
        if ( ruido(x,y) ) img(x,y) = 255;
    }
}

template <class T>
void gen_ruido_pimienta( CImg<T> &img, double sigma ) {
	/**
	 * Genera ruido pimienta (unicamente) en la imagen dada
	 */
    CImg<T> ruido ( img.width(), img.height(),1,1,0);
    ruido.noise( sigma, 2);
    cimg_forXY(img,x,y){
        if ( ruido(x,y) ) img(x,y) = 0;
    }
}


