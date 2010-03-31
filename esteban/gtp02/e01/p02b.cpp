#include <CImg.h>
#include <lut.h>
#include <stdio.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
 const char *filename = cimg_option( "-f", 
                                        "../../imagenes/earth.bmp", 
                                        "ruta archivo imagen" );
    int a = 1;
    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);

    for( int c=0; c<255; c++ ){
        lut( img1, a, c ).display(disp2);
        mapeo( a, c ).display(disp3);
        sleep(1);
    }
    
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
