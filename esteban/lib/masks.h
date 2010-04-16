#include <CImg.h>

using namespace cimg_library;

namespace masks {

    /**
       retorna una mascara impulso:
       *  0 0 0
       *  0 1 0
       *  0 0 0
     */
    CImg<float> impulso( ) {
        int x=3, y=3, z=1, c=1;
        CImg<float> mask( x, y, z, c, 0 );
        mask(1,1) = 1;
        return mask;
    }

    /**
       retorna una mascara promediadora sum{wi}/n*m
       *  1 1 1
       *  1 1 1 * 1/9
       *  1 1 1
     */
    CImg<double> media_estandar() {
        int x=3, y=3, z=1, c=1;
        double k = 1/9;
        CImg<double> mask( x, y, z, c, 1);
        cimg_forXY( mask, x, y ){ mask(x,y) *= k; }
        return mask;
    }

    /**
       retorna una mascara promediado ponderado
       *  1 2 1
       *  2 4 2 * 1/16
       *  1 2 1
     */
    CImg<float> media_ponderada() {
        int x=3, y=3, z=1, c=1;
        float k = 1/16;
        CImg<float> mask( x, y, z, c, 1 );
        mask(1,0) *= 2;
        mask(0,1) *= 2;
        mask(1,2) *= 2;
        mask(2,1) *= 2;
        mask(1,1) *= 4;
        cimg_forXY( mask, x, y ){ mask(x,y) *= k; }
        return mask;
    }


}
