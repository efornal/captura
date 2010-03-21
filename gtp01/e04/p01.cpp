#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    int normalizacion = 1; //0-255
    CImg<unsigned char> img1(256,256,1,1);

    cimg_forXY( img1, x, y ) {
        img1(x,y) = x;
    } 

    CImgDisplay disp( img1, "Tono de grises 0-255", normalizacion );
    
    while ( !disp.is_closed() && !disp.is_closed() ) {}

    return 0;
}
