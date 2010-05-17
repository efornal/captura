/**
 * La mascara gaussiana (en tiempo) tiene la propiedad que 
 * su T.Fourier tambien es una gaussiana
*/
#include <CHImg.h>
#include <iostream>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    //int wc = cimg_option( "-wc", 100, "frecuencia de corte" );
    int sigma = cimg_option( "-sigma", 1, "varianza del filtro gaussiano" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<double> img ( filename );
    
    CHImg<double> mask = masks::pa_gaussian( img.width(), sigma );

    CHImg<double> filtro = mask.get_fft_modulo();

    CImgList<double> list1( img.normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255) );
    list1.display(disp);
    disp.set_title("imagen original - modulo log");

    CImgList<double> list3( img.get_fft_modulo().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    list3.display(disp3);
    disp3.set_title("img original: modulo - fase");

    CImgList<double> list2( filtro.normalize(0,255),
                            filtro.get_fft_modulo_log().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("filtro - modulo log");

    CImgList<double> list4( filtro.get_fft_modulo().normalize(0,255),
                            filtro.get_fft_fase().normalize(0,255),
                            mask.normalize(0,255) );
    list4.display(disp4);
    disp4.set_title("filtro: modulo - fase - respuesta al impulso h(x,y), tiempo!");

    CHImg<double> filtrada = img.get_filtrada( filtro );

    CImgList<double> list5( filtrada.get_fft_modulo().normalize(0,255),
                            filtrada.get_fft_fase().normalize(0,255),
                            filtrada.get_fft_modulo_log().normalize(0,255) );
    list5.display(disp5);
    disp5.set_title("filtrada: modulo - fase - modulo log");

    filtrada.display("imagen filtrada");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
