#include <CImg.h>

using namespace cimg_library;

CImg<unsigned char> NOT ( CImg<unsigned char>img ) {
    cimg_forXY( img, x, y ) {
        img(x,y) /= 255; // (=0 || =1)
        img(x,y) = not( img(x,y) ) * 255; // (=0 || 255)
    }
    return img;
}

CImg<unsigned char> AND ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y)/255 && img2(x,y)/255 ) * 255;
    }
    return img1;
}

CImg<unsigned char> OR ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( (img1(x,y)/255) || (img2(x,y)/255) ) * 255;
    }
    return img1;
}

CImg<unsigned char> XOR ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( img1(x,y)/255 ^ img2(x,y)/255 ) * 255;
    }
    return img1;
}

CImg<unsigned char> NOTAND ( CImg<unsigned char>img1, CImg<unsigned char>img2 ) {
    cimg_forXY( img1, x, y ) {
        img1(x,y) = ( !(img1(x,y)/255) && img2(x,y)/255 ) * 255;
    }
    return img1;
}
