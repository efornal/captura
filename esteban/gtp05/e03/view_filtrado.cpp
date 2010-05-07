/**
 * FIXME:
 * porque con:
 * ./view_filtrado -wc 0 -f ../../imagenes/pattern.tif
 * hay colores (como el rojo) que desaparecen!?
*/
#include <CHImg.h>
#include <iostream>
#include <filtro.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    int wc = cimg_option( "-wc", 100, "frecuencia de corte" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6;


    CHImg<double> img ( filename );
    CHImg<double> filtro = filtro::pb_ideal( img, wc );

    img.normalize(0,255).display(disp);
    img.get_fft_modulo_log().normalize(0,255).display(disp2);
    img.get_fft_fase().normalize(0,255).display(disp3);

    disp.set_title("original");
    disp2.set_title("original: modulo log");
    disp3.set_title("original: fase");

    CHImg<double> filtrada = img.get_filtrada( filtro );

    filtrada.normalize(0,255).display(disp4);
    filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
    filtrada.get_fft_fase().normalize(0,255).display(disp6);

    disp4.set_title("filtrada");
    disp5.set_title("filtrada: modulo log");
    disp6.set_title("filtrada: fase");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.is_keyARROWDOWN () ){
            wc-=5;
            filtrada = img.get_filtrada( filtro::pb_ideal( img, wc ) );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);
            printf("wc: %d\n", wc);
        }
        if ( disp.is_keyARROWUP () ){
            wc+=5;
            filtrada = img.get_filtrada( filtro::pb_ideal( img, wc ) );
            filtrada = img.get_filtrada( filtro::pb_ideal( img, wc ) );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);
            printf("wc: %d\n", wc);
        }

    }
    return 0;
}
