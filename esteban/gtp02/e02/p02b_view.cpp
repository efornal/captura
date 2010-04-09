/**
   En log(1 + r), el 1 es para no hacer log(0) que no existe
*/
#include <CImg.h>
#include <math.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/rmn.jpg", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img1( filename );

    CImgDisplay disp, disp2, disp3;

    img1.display(disp);

    for (double factor=0; factor<2;factor=factor+0.02 ){
        lut_exp( img1, factor ).display(disp2);
        mapeo_exp( factor ).display(disp3);
        sleep(1);
    }

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
