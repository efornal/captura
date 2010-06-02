/**
 * ver:
 * ./view_filtrado_homomorfico -wc 275 -dw 5 -orden 5 -gl 0.35 -gh 1.01 -f ../../imagenes/reunion.tif
 * ./view_filtrado_homomorfico -f ../../imagenes/del-libro/test_pattern_blurring_orig.tif
 * ./view_filtrado_homomorfico -f ../../imagenes/reunion.tif
 *
 * gl   0 < gl < 1
 *   a >gl =>  mas  brillo medio (deja pasar  mas  bajas frec)
 *   a <gl => menos brillo medio (deja pasar menos bajas frec)
 * gh   gh > 1
 *   a >gh =>  mas  contraste ( aumenta  mas  las altas frec )
 *   a <gh => menos contraste ( aumenta menos las altas frec)
*/
#include <CHImg.h>
#include <iostream>
#include <filtro.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/casilla.tif", 
                                            "ruta archivo imagen" );
    double gl = cimg_option( "-gl",    0.0, "decremento brillo    0 < gl < 1" );
    double gh = cimg_option( "-gh",    1.0, "amplifica altas frec     gh > 1" );
    int wc    = cimg_option( "-wc",    1,   "frecuencia de corte" );
    int orden = cimg_option( "-orden", 2,  "orden del filtro (usa un butter)" );
    int dw    = cimg_option( "-dw",    1,   "delta frecuencia" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7, disp8;

    CHImg<double> img ( filename );

    CHImg<double> filtro = filtro::homomorfico( img, wc, gl, gh, orden );

    img.get_normalize(0,255).display(disp);
    img.get_fft_modulo_log().normalize(0,255).display(disp2);
    img.get_fft_fase().normalize(0,255).display(disp3);

    disp.set_title("original");
    disp2.set_title("original: modulo log");
    disp3.set_title("original: fase");

    CHImg<double> filtrada = img.get_filtrado_homomorfico( filtro );

    filtrada.get_normalize(0,255).display(disp4);
    filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
    filtrada.get_fft_fase().normalize(0,255).display(disp6);

    filtro.get_fft_modulo_log().normalize(0,255).display(disp7);
    filtro.get_fft_fase().normalize(0,255).display(disp8);

    disp4.set_title("filtrada");
    disp5.set_title("filtrada: modulo log");
    disp6.set_title("filtrada: fase");

    disp7.set_title("filtro: modulo log");
    disp8.set_title("filtro: fase");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.is_keySHIFTLEFT () && disp.is_keyARROWDOWN () ){
            wc -= dw; printf("wc: %d\n", wc);
            goto calcular;
        }
        if ( disp.is_keySHIFTLEFT () && disp.is_keyARROWUP () ){
            wc += dw; printf("wc: %d\n", wc);
            goto calcular;
        }

        if ( disp.is_keySHIFTLEFT () && disp.is_keyARROWLEFT  () ) { 
            orden--; printf("orden: %d\n", orden); 
            goto calcular;
        }
        if ( disp.is_keySHIFTLEFT () && disp.is_keyARROWRIGHT () ) { 
            orden++; printf("orden: %d\n", orden); 
            goto calcular;
        }

        if ( !disp.is_keySHIFTLEFT () && disp.is_keyARROWLEFT () ) { 
            gl-=0.05; printf("gl [0,1] brillo: %f\n", gl); 
            goto calcular;
        }
        if ( !disp.is_keySHIFTLEFT () && disp.is_keyARROWRIGHT () ) { 
            gl+=0.05; printf("gl [0,1] brillo: %f\n", gl); 
            goto calcular;
        }

        if ( !disp.is_keySHIFTLEFT () && disp.is_keyARROWDOWN () ) { 
            gh--; printf("gh [>1]: %f\n", gh); 
            goto calcular;
        }
        if ( !disp.is_keySHIFTLEFT () && disp.is_keyARROWUP () ) { 
            gh++; printf("gh [>1]: %f\n", gh); 
            goto calcular;
        }

        if ( disp.is_keyPAGEUP()   ) { 
            dw--; printf("dw: %d\n", dw); 
            goto calcular;
        }
        if ( disp.is_keyPAGEDOWN() ) { 
            dw++; printf("dw: %d\n", dw); 
            goto calcular;
        }

        goto saltar;
    calcular:
        filtro = filtro::homomorfico( img, wc, gl, gh, orden );
        filtrada = img.get_filtrado_homomorfico( filtro );
        filtrada.normalize(0,255).display(disp4);
        filtrada.get_fft_modulo_log().normalize(0,255).display(disp5);
        filtrada.get_fft_fase().normalize(0,255).display(disp6);

        filtro.get_fft_modulo_log().normalize(0,255).display(disp7);
        filtro.get_fft_fase().normalize(0,255).display(disp8);
    saltar:
        printf("");


    }
    return 0;
}
