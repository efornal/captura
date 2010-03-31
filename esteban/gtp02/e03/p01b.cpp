/**
   FIXME: como es el reescalado?? sumar 255  y dividir por 2??
*/

#include <CImg.h>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f1", "../../imagenes/rmn.jpg", 
                                        "ruta archivo imagen 1" );
    const char *filename2 = cimg_option( "-f2", "../../imagenes/rmn.jpg", 
                                        "ruta archivo imagen 2" );

    CImg<unsigned char> img1( filename1 );
    CImg<unsigned char> img2( filename2 );

    CImgDisplay disp, disp2, disp3;


    img1.display(disp);
    img2.display(disp2);
    //???    resta(img1,img2).display(disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
