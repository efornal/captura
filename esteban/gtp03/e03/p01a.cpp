/**
 * Variasiones de filtrados promediadores
*/
#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::signo_mas() ).normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada con mask forma signo mas");

    img.get_convolve( masks::media_estandar() ).normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada con media estandar");

    img.get_convolve( masks::media_ponderada() ).normalize(0,255).display(disp4);
    disp4.set_title("imagen filtrada con media ponderada");

    masks::signo_mas().normalize(0,255).display("signo mas");
    masks::media_estandar().normalize(0,255).display("media estandar - norm");
    masks::media_ponderada().normalize(0,255).display("media ponderada - norm");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
