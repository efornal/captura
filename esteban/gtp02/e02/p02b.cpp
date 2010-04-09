#include <CImg.h>
#include <math.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/rmn.jpg", 
                                        "ruta archivo imagen" );
    const double factor = cimg_option( "-v", 1.01, 
                                      "valor exponencial" );
    CImg<unsigned char> img1( filename );

    CImgDisplay disp, disp2, disp3;

    CImg<unsigned char> img2 = lut_exp( img1, factor );

    img1.display(disp);
    img2.display(disp2);
    
    mapeo_exp( factor ).display(disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
