/**
 * FIXME: no funciona!
 * porque si funciona cuando lo paso por parametro:
 * ./view_filtrado_gaussian_tiempo -sigma 1.0
 * ./view_filtrado_gaussian_tiempo -sigma 1.9
 * ./view_filtrado_gaussian_tiempo -sigma 2.5 ...etc
 * pero no cuando varío el delta dx=0.1 con las teclas !?????
 *
 * ver: ./view_filtrado_gaussian_tiempo -f ../../imagenes/del-libro/test_pattern_blurring_orig.tif
*/
#include <CHImg.h>
#include <iostream>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    double sigma    = cimg_option( "-sigma", 0.001, "varianza" );
    double dw       = cimg_option( "-dw", 0.1, "delta de varianza" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6;

    CHImg<double> img ( filename );
    CHImg<double> mask = masks::gaussian( img.width(), sigma );
    CHImg<double> filtro = mask.get_fft_modulo();

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
            sigma -= dw;
            mask = masks::gaussian( img.width(), sigma );
            filtro = mask.get_fft_modulo();
            filtrada = img.get_filtrada( filtro );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);

            printf("sigma: %f\n", sigma);
        }
        if ( disp.is_keyARROWUP () ){
            sigma += dw;
            mask = masks::gaussian( img.width(), sigma );
            filtro = mask.get_fft_modulo();
            filtrada = img.get_filtrada( filtro );
            filtrada.normalize(0,255).display(disp4);
            filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
            filtrada.get_fft_fase().normalize(0,255).display(disp6);
            printf("sigma: %f\n", sigma);
        }

        if ( disp.is_keyARROWLEFT  () ) { 
            dw-=0.001; 
            printf("dw: %f\n", dw); 
        }
        if ( disp.is_keyARROWRIGHT () ) { 
            dw+=0.001; 
            printf("dw: %f\n", dw); 
        }

    }
    return 0;
}
