/**
 * CImg histogram ( int nb_levels,
 *                      value_min = 0,
 *                      value_max = 0 )
 */

#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    const int niveles = cimg_option( "-n", 10, "numero de niveles de ecualizado" );
    const int tipo_ploteo = cimg_option( "-t", 3, "tipo display histograma (1-4?)" );

    CImg<unsigned char> img ( 6,6,1,1,10 );
    CImgDisplay disp, disp2, disp3, disp4;
    img(0,0) = 1;
    img(1,0) = 2;
    img(3,3) = 3;
    img(3,4) = 4;
    img(5,5) = 5;
    img(3,5) = 4;
    img(5,1) = 5;

    img.get_histogram( niveles, 0, niveles ).display_graph( disp , tipo_ploteo );
    disp.set_title("histograma con n = 10");

    img.get_histogram( 5, 0, 5 ).display_graph( disp2 , tipo_ploteo );
    disp2.set_title("histograma con n = 5");

    img.display(); 

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {wait();}
    return 0;
}
