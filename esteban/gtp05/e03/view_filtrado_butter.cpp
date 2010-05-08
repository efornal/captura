/**
 * ver: /view_filtrado_butter -f ../../imagenes/del-libro/test_pattern_blurring_orig.tif
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
    int dw = cimg_option( "-dw", 1, "delta de frecuencia" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6;


    CHImg<double> img ( filename );
    CHImg<double> filtro = filtro::pb_butter( img, wc );

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
            wc -= dw;
            filtrada = img.get_filtrada( filtro::pb_butter( img, wc ) );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);
            printf("wc: %d\n", wc);
        }
        if ( disp.is_keyARROWUP () ){
            wc += dw;
            filtrada = img.get_filtrada( filtro::pb_butter( img, wc ) );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);
            printf("wc: %d\n", wc);
        }
        if ( disp.is_keyARROWLEFT () ) {
            dw--;
            printf("dw: %d\n", dw);
        }
        if ( disp.is_keyARROWRIGHT () ) {
            dw++;
            printf("dw: %d\n", dw);
        }
    }
    return 0;
}
