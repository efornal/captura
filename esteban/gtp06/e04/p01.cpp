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
    int wc = cimg_option( "-wc", 114, "frecuencia de corte" );
    int ancho = cimg_option( "-ancho", 2, "ancho de la banda" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ),
        filtro ( filtro::rb_ideal( img.width(), img.width(), wc, ancho) );

    img.channel(0);
    img.display(disp);

    CImgList<double> lista( img.get_fft_modulo().normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    lista.display(disp2);

    disp.set_title("originial");
    disp2.set_title("modulo - modulo log - fase");

    img.get_fft_modulo(false).normalize(0,255).display("localizar punto");

    filtro.get_normalize(0,255).display(disp3);
    disp3.set_title("filtro rechaza banda");

    img.get_filtrada( filtro ).get_normalize(0,255).display(disp4);
    disp4.set_title("filtrada");
        
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
