/**
 * FIXME: radio de la esfera
 * 1) el centro de la esfera es el punto seleccionado!? por que
 * dice valor medio de cada componente ??
 * 
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/futbol.jpg", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img ( filename ); 
    CImgDisplay disp;

    img.display(disp);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.button() && disp.mouse_y() >= 0  &&  disp.mouse_x() >= 0 ) {

            printf ("color: R=%d G=%d B=%d \n", 
                    img( disp.mouse_x(), disp.mouse_x(), 0, 0 ),
                    img( disp.mouse_x(), disp.mouse_x(), 0, 1 ),
                    img( disp.mouse_x(), disp.mouse_x(), 0, 2 ) );
            
        }


    }
    return 0;
}
