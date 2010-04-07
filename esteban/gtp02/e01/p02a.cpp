#include <CImg.h>
#include <lut.h>
#include <stdio.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
 const char *filename = cimg_option( "-f", 
                                        "../../../imagenes/earth.bmp", 
                                        "ruta archivo imagen" );
    int c = 0;
    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);

    for( int a=0; a<255; a++ ){
        lut( img1, a, c ).display(disp2);
        mapeo( a, c ).display(disp3);
        cout << " a = " << a << endl;
        sleep(1);
    }

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
