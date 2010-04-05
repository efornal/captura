#include <CImg.h>

using namespace cimg_library;

/**
   Imagen cuadrada de tamanio segun cantidad de tonos
*/
CImg<unsigned char> tonos_de_gris( int tonos ){

    CImg<unsigned char> img( tonos, tonos, 1, 1 );

    cimg_forXY( img, x, y ) {
        img(x,y) = x;
    } 

    return img;
}
