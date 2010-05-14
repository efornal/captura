#define pdi_restauracion 1
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#ifndef MAX_LINE_LENGTH
#include <CPDSI_functions.h>
#endif

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

/**
 * Genera ruido gausiano en la imagen dada
 */
void gen_ruido_gaussiano( CImg<double> &img, double sigma ) {
    img.noise( sigma, 0); // gaussian = 0
}

/**
 * Genera ruido uniforme en la imagen dada
 */
void gen_ruido_uniforme( CImg<double> &img, double sigma ) {
    img.noise( sigma, 1);
}

/**
 * Genera ruido sal y pimienta en la imagen dada
 */
void gen_ruido_sal_y_pimienta( CImg<double> &img, double sigma ) {
    img.noise( sigma, 2); 
}

/**
 * Genera ruido sal (unicamente) en la imagen dada
 */
void gen_ruido_sal( CImg<double> &img, double sigma ) {
    CImg<double> ruido ( img.width(), img.height(),1,1,0);
    ruido.noise( sigma, 2);
    cimg_forXY(img,x,y){
        if ( ruido(x,y) ) img(x,y) = 255;
    }
}

/**
 * Genera ruido pimienta (unicamente) en la imagen dada
 */
void gen_ruido_pimienta( CImg<double> &img, double sigma ) {
    CImg<double> ruido ( img.width(), img.height(),1,1,0);
    ruido.noise( sigma, 2);
    cimg_forXY(img,x,y){
        if ( ruido(x,y) ) img(x,y) = 0;
    }
}

//====================================================
//                filtros espaciales 
//====================================================

/**
 * retorna un filtro espacial de media geometrica
 */
CImg<double> filtrar_geometrica( CImg<double> img, int size=3) {
    CImg<double> mask (size,size,1,1,0);
    CImg<double> filtrada (img);
    double prod;
    int mid = size/2;
 
    cimg_forXY(img,x,y){
         prod = 1.0;
        
        mask = img.get_crop( x-mid, y-mid, x+mid, y+mid, true );            
        cimg_forXY(mask,s,t) {
            prod *= mask(s,t);
        }
        filtrada(x,y) = pow( prod, (1.0/(size*size)) );
    }

    return filtrada;
}

/* CImg<double> filtrar_geometrica( CImg<double> img, int size=3) { */
/*     CImg<double> mask (size,size,1,1,0); */
/*     CImg<double> filtrada (img); */
/*     double prod; */

/*     cimg_forXY(img,x,y) { */
/*         prod = 1; */
/*         mask = img.get_crop( x-1, y-1, x+1, y+1, true );             */

/*         cimg_forXY(mask,s,t) { */
/*             prod *= mask(s,t); */
/*         } */
/*         filtrada(x,y) = pow( prod, (1/(size*size)) ); */
/*     } */

/*     return filtrada; */
/* } */
