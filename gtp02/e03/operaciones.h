#include <CImg.h>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> suma( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    return (img1 + img2) / 2;
}


CImg<unsigned char> enmascarar( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    CImg<unsigned char> mascara( img1.width(), img1.height(), 1, 1);
    cimg_forXY(img1,x,y){
        mascara(x,y) = img1(x,y) * img2(x,y);
    }
    return mascara;
}

CImg<unsigned char> division( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    CImg<unsigned char> result( img1.width(), img1.height(), 1, 1);
    cimg_forXY(img1,x,y){
        result(x,y) = img1(x,y) / img2(x,y);
    }
    return result;
}
