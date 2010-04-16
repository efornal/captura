/**
* CImg<T>& correlate( CImg< t > &mask,
* 		    int cond = 1,
* 		    bool weighted_correl = false ) 
*
* CImg<T>& convolve ( CImg< t > &mask,
*                     int	cond = 1,
*                     bool weighted_convol = false)
*/

#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    CImg<float> mask = masks::impulso();
    CImgDisplay disp, disp2;
    CImg<float> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.convolve( mask );


    img.display(disp2);
    disp2.set_title("imagen filtrada con impulso, debe ser igual");

    mask.display("kernel");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
