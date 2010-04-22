#include <CHImg.h>
#include <masks.h>
#include <iostream>

using namespace cimg_library;
using namespace std;
using namespace masks;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename );

    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::impulso() ).display(disp2);
    disp2.set_title("imagen filtrada con impulso, debe ser igual");
    masks::impulso().display("impulso");

    img.get_convolve( masks::media_estandar() ).normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada con media estandar");
    masks::media_estandar().normalize(0,255).display("media estandar - norm");

    img.get_convolve( masks::media_ponderada() ).normalize(0,255).display(disp4);
    disp4.set_title("imagen filtrada con media ponderada");
    masks::media_ponderada().normalize(0,255).display("media ponderada - norm");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
