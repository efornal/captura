/**
 * FIXME: confirmar
 * Por el normalizado, en el display del filtro,  no se nota 
 * la diferencia para diferentes valores de gl y gh.
 *
 * para la otra imagen: ./p01 -f ../../imagenes/reunion.tif
 *                                      ____
 *   1_    ____gh   1_ _---gh   1_    _-    gh
 *    |  _-          |_-         |  _-
 * gl |_-            |           |_-
 *    |_________     |________   |_________
 *
 *     0 < gl < 1    gh > 1
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
    double gl = cimg_option( "-gl", 0.0, "decremento brillo    0 < gl < 1" );
    double gh = cimg_option( "-gh", 1.0, "amplifica altas frec     gh > 1" );
    double wc = cimg_option( "-wc", 1.0, "frecuencia de corte" );
    int orden = cimg_option( "-orden", 2, "orden del filtro (usa un butter)" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<double> img ( filename );
    img.channel(0);

    CHImg<double> filtro = filtro::homomorfico( img, wc, gl, gh, orden );

    CImgList<double> list1( img.get_normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    list1.display(disp);
    disp.set_title("imagen original - modulo log - fase");

    CImgList<double> list2( filtro.get_normalize(0,255),
                            filtro.get_fft_modulo_log().normalize(0,255),
                            filtro.get_fft_fase().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("filtro - modulo log - fase");

    CHImg<double> filtrada = img.get_filtrado_homomorfico( filtro );

    CImgList<double> list5( filtrada.get_normalize(0,255),
                            filtrada.get_fft_modulo_log().normalize(0,255),
                            filtrada.get_fft_fase().normalize(0,255) );
    list5.display(disp5);
    disp5.set_title("filtrada: modulo - modulo log - fase");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
