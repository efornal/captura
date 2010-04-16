/**
 * Si la mascara es simetrica, hacer la conv o la corr es lo mismo
 * y el MSE (error cuadratico medio) entre ambas da 0
 * si no es simetrica, el MSE  es != 0
*/

#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    CImgDisplay disp, disp2, disp3, disp4, disp5;
    CImg<float> img( filename ), img_conv, img_corr, img_corr_asim, img_conv_asim;

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

    img_corr_asim = img.get_correlate( masks::asimetrica() );
    img_corr_asim.print("img_corr_asim");
    img_corr_asim.normalize(0,255).display(disp4);
    disp4.set_title("correlacion con asimetrica");

    img_conv_asim = img.get_convolve( masks::asimetrica() );
    img_conv_asim.print("img_conv_asim");
    img_conv_asim.normalize(0,255).display(disp5);
    disp5.set_title("convolucion con asimetrica");

    printf ("MSE orig-corr: %f \n", img.MSE(img_corr) );
    printf ("MSE orig-conv: %f \n", img.MSE(img_conv) );
    printf ("MSE conv-corr: %f (son iguales!) \n", img_corr.MSE(img_conv) );
    printf ("MSE conv-corr asim: %f (son diferentes!) \n", img_corr_asim.MSE(img_conv_asim) );

    masks::media_ponderada().normalize(0,255).display("mask");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
