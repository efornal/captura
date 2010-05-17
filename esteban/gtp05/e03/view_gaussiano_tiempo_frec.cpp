/**
 * La mascara gaussiana (en tiempo) tiene la propiedad que 
 * su T.Fourier tambien es una gaussiana
 * 
 * 
*/
#include <CHImg.h>
#include <iostream>
#include <masks.h>
#include <filtro.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    int sigma = cimg_option( "-sigma", 10, "varianza del filtro gaussiano" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<double> img ( filename );
    
    CHImg<double> mask = masks::gaussian( img.width(), sigma );

    CHImg<double> filtro = filtro::pb_gaussiano( img, sigma );

    CImgList<double> list1( mask.normalize(0,255),
                            mask.get_fft_modulo_log().normalize(0,255),
                            mask.get_fft_fase().normalize(0,255) );
    list1.display(disp);
    disp.set_title("mask, filtro en tiempo: gaussiano");

    CImgList<double> list2( filtro.normalize(0,255),
                            filtro.get_fft_modulo_log().normalize(0,255),
                            filtro.get_fft_fase().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("filtro en frecuencia: gaussiano");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
