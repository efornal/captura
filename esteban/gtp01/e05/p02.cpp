/**
   FIXME:
     1. Esta bien hecho el submuestreo con resize como abajo?
 */
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const int factor = cimg_option( "-f", 2, "factor de submuestreo" );

    CImg<unsigned char> img1( "../../imagenes/rmn.jpg" );

    CImgDisplay disp ( img1, "imagen rmn.jpg", 1 );

    img1.print();
    
    img1.get_resize( (int)(img1.width()/factor), (int)(img1.height()/factor) ).
        display();

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
