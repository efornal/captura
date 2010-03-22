#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    CImg<unsigned char> img1( "../../imagenes/huang2.jpg" );

    CImgDisplay disp ( img1, "imagen", 1 );

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
