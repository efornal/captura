/**
 * TODO : solo fase verificar!?
 */

#include <espectro.h>
#include <CHImg.h>
#include <iostream>


using namespace cimg_library;
using namespace std;


int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img ( filename );

    CImgList<double> list1( img.get_solo_modulo().normalize(0,255),
                            img.get_solo_fase().normalize(0,255) );
    list1.display(disp2);
    
    img.display(disp);
    disp.set_title("imagen");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
