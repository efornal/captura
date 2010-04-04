#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> menor ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y) < img2(x,y) ) ? 0 : 255;
    }
    return img1;
}

CImg<unsigned char> menor_igual ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y) <= img2(x,y) ) ? 0 : 255;
    }
    return img1;
}

CImg<unsigned char> mayor ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y) > img2(x,y) ) ? 0 : 255;
    }
    return img1;
}

CImg<unsigned char> mayor_igual ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y) >= img2(x,y) ) ? 0 : 255;
    }
    return img1;
}

