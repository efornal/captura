/**
 * El equalizado local permite rezaltar detalles que en un
 * equalizado global no quedan visibles
 *   FIXME: 
 * 1) porque no funciona con la imagen de los cuadros:
 *   ../../imagenes/ej7a.tif
 * 2) porque la imagen se ve mal, pixelada?
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    int dx = cimg_option( "-dx", 3, "dx mask" );
    int dy = cimg_option( "-dy", 3, "dy mask" );
    int nivel = cimg_option( "-n", 255, "nivel equalize" );

    CImgDisplay disp, disp2, disp3, disp4,disp5;
    CHImg<double> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.get_local_equalize(dx,dy,nivel).display(disp4);
    disp4.set_title("equalizacion local");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();

        if ( disp.is_keyARROWUP () ){
            ++nivel;
            img.get_local_equalize(dx,dy,nivel).display(disp4);
            printf("nivel: %d \n",nivel);
        }

        if ( disp.is_keyARROWDOWN () ){
            --nivel;
            img.get_local_equalize(dx,dy,nivel).display(disp4);
            printf("nivel: %d \n",nivel);
        }


    }
    return 0;
}
