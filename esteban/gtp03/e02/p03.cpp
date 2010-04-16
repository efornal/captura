/**
 * 
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
    CImg<float> img( filename ), img_conv, img_corr;

    img.display(disp);
    disp.set_title("imagen original");

    img_conv = img.get_convolve( masks::media_ponderada() );
    img_conv.print("img_conv");
    img_conv.normalize(0,255).display(disp2);
    disp2.set_title("convolucion");

    img_corr = img.get_correlate( masks::media_ponderada() );
    img_corr.print("img_corr");
    img_corr.normalize(0,255).display(disp3);
    disp3.set_title("correlacion");

    printf ("MSE orig-corr: %f \n", img.MSE(img_corr) );
    printf ("MSE orig-conv: %f \n", img.MSE(img_conv) );
    printf ("MSE conv-corr: %f \n (son iguales!)", img_corr.MSE(img_conv) );

    masks::media_ponderada().normalize(0,255).display("mask");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
