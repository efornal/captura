/**
 * FIXME: porque la imagen se ve afectada (cambia el aspecto)
 * solo cuando el facto A varia entre -10 y 10 ?
 * VARIAR FACTOR CON FLECHAS!
*/
#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/estanbul.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CHImg<double> img( filename );
    
    img.display(disp);
    disp.set_title("imagen original");

    int factor = 1;
    img.get_alta_potencia( masks::suma_uno_medio(), factor ).
        normalize(0,255).display(disp3);
    disp3.set_title("alta potencia");
    printf("factor: %f\n",factor);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();

        if ( disp.is_keyARROWDOWN () ){
            --factor;
            img.get_alta_potencia( masks::suma_uno_medio(), factor ).
                normalize(0,255).display(disp3);
            disp3.set_title("alta potencia");
            printf("factor: %d \n",factor);
        }

        if ( disp.is_keyARROWUP () ){
            ++factor;
            img.get_alta_potencia( masks::suma_uno_medio(), factor ).
                normalize(0,255).display(disp3);
            disp3.set_title("alta potencia");
            printf("factor: %d \n",factor);
        }

    }
    
    return 0;
}
