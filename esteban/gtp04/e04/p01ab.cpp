/**
 * Des histograma se puede decir que el inervalo para el negro (color del rio)
 * esta mas o menos de 0-20
 * 
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/rio.jpg", 
                                        "ruta archivo imagen" );

    CHImg<double> img ( filename );
    CImgDisplay disp, disp2, disp3, disp4;
    img.display(disp);
    disp.set_title("imagen original");

    img.get_histogram(256).display_graph(disp3,3);
    img.display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
