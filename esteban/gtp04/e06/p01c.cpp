/**
 * FIXME: histograma
 * 1) Cómo determino el radio de la esfera a partir del histograma???
 * 
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/futbol.jpg", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img ( filename ); 
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp);

    img.get_channel(0).get_histogram(255).display_graph( disp2, 3 );
    img.get_channel(1).get_histogram(255).display_graph( disp3, 3 );
    img.get_channel(2).get_histogram(255).display_graph( disp4, 3 );

    disp2.set_title("canal R");
    disp3.set_title("canal G");
    disp4.set_title("canal B");

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
