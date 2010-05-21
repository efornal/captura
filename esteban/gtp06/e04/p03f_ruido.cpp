/**
 * punto (70,90)
 * => radio = sqrt{70^2 + 90^2} = 114.0 = wc
*/
#include <CHImg.h>
#include <filtro.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/img_degradada.tif",
                                         "ruta archivo imagen" );
    int uc = cimg_option( "-uc", 70, "frecuencia de corte" );
    int vc = cimg_option( "-vc", 90, "frecuencia de corte" );
    int ancho = cimg_option( "-ancho", 100, "ancho de la banda" );
    int orden = cimg_option( "-orden", 2, "orden del filtro de butter" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ),
        filtro ( filtro::ab_gaussiano_notch( img.width(), img.width(), 
                                          uc, vc , ancho) );

    img.channel(0);
    img.display(disp);
    disp.set_title("originial");

    CImgList<double> lista( img.get_fft_modulo().normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    lista.display(disp2);
    disp2.set_title("modulo - modulo log - fase");

    filtro.get_normalize(0,255).display(disp3);
    disp3.set_title("filtro pasa banda");

    CHImg<double> filtrada = img.get_filtrada( filtro );
    filtrada.get_normalize(0,255).display(disp4);
    disp4.set_title("filtrada");

    CImgList<double> lista2( filtrada.get_fft_modulo().normalize(0,255),
                             filtrada.get_fft_modulo_log().normalize(0,255),
                             filtrada.get_fft_fase().normalize(0,255) );
    lista2.display(disp5);
    disp5.set_title("espectro de filtrada: modulo - modulo log - fase");

    img.get_fft_modulo(false).normalize(0,255).display("acá localizar el punto");        

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
