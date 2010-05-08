/**
 * El filtrado es mucho mejor, no hay gibbs !!
 * FIXME: porque la fase no varía ?? comparando con el filtrado
 * ideal, ver: view_filtrado_ideal
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

    CImgDisplay disp, disp2, disp3, disp4, disp5;


    CHImg<double> img ( filename );
    CHImg<double> filtro = filtro::pb_butter( img, wc );

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
                            filtro.get_fft_fase().normalize(0,255) );
    list4.display(disp4);
    disp4.set_title("filtro: modulo - fase");

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
