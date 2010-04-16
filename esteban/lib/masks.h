#include <CImg.h>

using namespace cimg_library;

namespace masks {

    /**
       retorna una mascara impulso:
       *  0 0 0
       *  0 1 0
       *  0 0 0
     */
    CImg<float> impulso(int x=3, int y=3, int z=1, int c=1, int valor=0 ) {
        CImg<float> mask( x, y, z, c, valor );
        mask(1,1) = 1;
        return mask;
    }

    /* CImg<float> media_estandar() { */
    /*     CImg<float> mask(3,3,1,1,0); */
    /*     mask(1,1) = 1; */
}
