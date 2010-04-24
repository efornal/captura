#include <color.h>
#include <CHImg.h>
#include <iostream>
#include <imagenes.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );
    int paleta = cimg_option("-p", 1,"nro paleta [1-8]");

    CHImg<double> img (  tonos_de_gris(256) );
    CImgDisplay disp, disp2, disp3, disp4;
    img.display(disp);
    disp.set_title("imagen original");

    img.get_aplicar_paleta( paleta ).display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
