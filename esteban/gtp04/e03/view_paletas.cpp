#include <color.h>
#include <CHImg.h>
#include <iostream>
#include <imagenes.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CHImg<double> img (  filename );
    CImgDisplay disp, disp2, disp3, disp4;
    img.display(disp);
    disp.set_title("imagen original");

    int paleta = 1;
    img.get_aplicar_paleta(paleta).display(disp2);
    disp.set_title("imagen otra paleta");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.is_keyARROWDOWN () ){
            --paleta;
            img.get_aplicar_paleta(paleta).display(disp2);
            printf("paleta: %d \n",paleta);
        }

        if ( disp.is_keyARROWUP () ){
            ++paleta;
            img.get_aplicar_paleta(paleta).display(disp2);
            printf("paleta: %d \n",paleta);
        }


    }

    return 0;
}
