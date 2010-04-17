/**
 * CImg histogram ( int nb_levels,
 *                      value_min = 0,
 *                      value_max = 0 )
 * CImg equalize ( int nb_levels,
 *                     value_min = 0,
 *                     value_max = 0 )	 
 * CImg display_graph ( CImgDisplay &disp, 
 *                              int plot_type=1, 
 *                              int vertex_type=1, 
 *                              ...lavels )
 * CImg display_graph ( char *const title=0, 
 *                            int plot_type=1, 
 *                            int vertex_type=1, 
 *                            ...lavels )
 * NOTA:
 * ojo , si se especifican los valores value_min , value_max
 * es como hacer un zoom en esa zona, no se ve el histo completo,
 */

#include <CImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    const int niveles = cimg_option( "-n", 256, "numero de niveles de ecualizado" );
    const int tipo_ploteo = cimg_option( "-t", 3, "tipo display histograma (1-4?)" );

    CImg<unsigned char> img ( filename );
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    disp.set_title("original");

    img.get_equalize( niveles ).display( disp2 );
    disp2.set_title("equalizada con 256");
    
    img.get_histogram( niveles, 0, 255 ).display_graph( disp3 , tipo_ploteo );
    disp3.set_title("histograma");

    img.get_equalize( niveles ).
        get_histogram( niveles , 0, 255 ).
        display_graph( disp4, tipo_ploteo );
    disp4.set_title("histograma de imagen equalizada");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
