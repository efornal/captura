#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

CImg<unsigned char> lut( CImg<unsigned char> img1, int a=1, int c=0 ) {

    CImg<unsigned char> img2(img1.width(),img1.height(),1,1);
    cimg_forXY( img1, x, y ) {
        img2(x,y) =  a*img1(x,y) + c;
    }
    return img2; 
}

int main() {

    CImg<unsigned char> img1("../../imagenes/orion.jpg");

    CImgDisplay disp,disp2;

    img1.channel(1);

    CImg<unsigned char> img2 = lut(img1);

    img1.display(disp);
    img2.display(disp2);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
