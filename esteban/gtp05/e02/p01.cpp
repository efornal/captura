/**
 * El aporte de la fase dice mucho mas de la imagen que el modulo
 * con solo fase la imagen pude verse bien
 * con solo modulo, no se aprecia nada de la imagen
 */

#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/avion.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img ( filename );

    CImgList<double> list2( img.get_fft_modulo().normalize(0,255),
                            img.get_fft_fase().normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255) );
    list2.display(disp3);
    disp3.set_title("modulo - fase - modulo log");

    CImgList<double> list1( img.get_a_solo_modulo().log().normalize(0,255),
                            img.get_a_solo_fase().normalize(0,255) );
    list1.display(disp2);
    disp2.set_title("img de solo modulo - img de solo fase");
    
    img.display(disp);
    disp.set_title("imagen original");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
