#include <CImg.h>
#include <lut.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/earth.bmp", 
                                        "ruta archivo imagen" );
    int c, a = -1;
    CImg<unsigned char> img1( filename );
    c = img1.max();
    CImgDisplay disp, disp2, disp3;

    CImg<unsigned char> img2 = lut( img1, a, c );

    img1.display(disp);
    img2.display(disp2);
    
    mapeo( a, c ).display(disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
