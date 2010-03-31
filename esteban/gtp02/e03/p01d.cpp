/**
   FIXME: se implementa como la recíproca de la otra? como?
     - la division por cero queda de cualquier modo!?
     - para que se usa?
*/
#include <CImg.h>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f1", "../../imagenes/letras2.tif", 
                                         "ruta archivo imagen 1" );
    const char *filename2 = cimg_option( "-f2", "../../imagenes/letras2.tif", 
                                         "ruta archivo imagen 1" );
    CImg<unsigned char> img1( filename1 );
    CImg<unsigned char> img2( filename2 );

    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    img2.display(disp2);
    division(img1,img2).display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
