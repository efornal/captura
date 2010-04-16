/**
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

    masks::mask(3,3).normalize(0,255).display("mask 3x3");
    masks::mask(5,5).normalize(0,255).display("mask 5x5");
    masks::mask(20,20).normalize(0,255).display("mask 20x20");

    img_conv = img.get_convolve( masks::mask(3,3) );
    img_conv.print("img_conv_3x3");
    img_conv.normalize(0,255).display(disp2);
    disp2.set_title("mask 3x3");

    img_corr = img.get_correlate( masks::mask(5,5) );
    img_corr.print("img_corr_5x5");
    img_corr.normalize(0,255).display(disp3);
    disp3.set_title("mask 5x5");

    img_corr = img.get_correlate( masks::mask(20,20) );
    img_corr.print("img_corr_20x20");
    img_corr.normalize(0,255).display(disp3);
    disp3.set_title("mask 20x20");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
