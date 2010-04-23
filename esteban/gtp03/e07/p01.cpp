/**
 *   FIXME: no funciona la mascara no se como se usa!!
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/ej7a.tif", 
                                        "ruta archivo imagen" );
    const int dx = cimg_option( "-dx", 3, "dx mask" );
    const int dy = cimg_option( "-dy", 3, "dy mask" );
    const int nivel = cimg_option( "-n", 255, "nivel equalize" );

    CImgDisplay disp, disp2, disp3, disp4,disp5;
    CHImg<double> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.get_local_equalize(dx,dy,nivel).display(disp4);
    disp4.set_title("equalizacion local");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }
    return 0;
}
