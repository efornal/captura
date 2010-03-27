#include <CImg.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/clown.jpg", 
                                        "ruta archivo imagen" );
    int a = 1, c = 0;
    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2;

    CImg<unsigned char> img2 = lut( img1, a, c );

    img1.display(disp);
    img2.display(disp2);
    
    ver_mapeo( a, c );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
