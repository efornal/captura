#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> plano_de_bit( CImg<unsigned char> img, int nro=0 ){
    if ( nro > 0 ) {
        cimg_forXY(img,x,y){
            img(x,y) = (img(x,y) >> nro) &0x00000001;
        }
    } else{
        cimg_forXY(img,x,y){
            img(x,y) = (img(x,y)) &0x00000001;
        }
    }
    return img;
}
