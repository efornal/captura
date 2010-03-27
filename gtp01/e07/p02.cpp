/**
FIXME: no funciona al redimencionar?, porque?
*/

#include <CImg.h>
#include <stdio.h>
#include <medios_tonos.h>

using namespace std;
using namespace cimg_library;

int main( int argc, char **argv ) {

    CImgDisplay disp;

    CImg<unsigned char> img1(256,255,1,1);

    cimg_forXY( img1, x, y ) {
        img1(x,y) = x;
    } 
    
    img1.display( disp );

    CImg<unsigned char> mediotono = to_medio_tono( img1 );

    mediotono.display();

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
