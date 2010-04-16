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
    CImgDisplay disp, disp2, disp3;
    CImg<float> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::media_ponderada() ).normalize(0,255).display(disp2);
    disp2.set_title("convolucion");

    masks::media_ponderada().normalize(0,255).display("mask");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
