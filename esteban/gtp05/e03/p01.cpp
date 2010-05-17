/**
 * FIXME: 
 * 1-) al variar el tamaño del filtro varia el tamaño el cuadrado?
 * 2-) Estan bien estas conclusiones: ?
 *
 * Si no se varia el tamaño del cuadrado y si el del filtro:
 * entonces al aumentar el tamaño el filtro mantiene mas componentes
 * frecuenciales, bajas en este caso. Es decir: aumenta la frecuencia
 * de corte. 
 * |           |
 * |_.___  =>  |___._
 *    w            w
 * De todos modos, la el filtro siempre tiene el mismo tamaño de la img?
 */
#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/avion.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img1 ( 25,25,1,1,0 ),
        img2 ( 100,100,1,1,0 ),
        img3 ( 200,200,1,1,0 );
    unsigned char color[] = {255,255,255};

    img1.draw_rectangle(11,11,15,15,color);
    img2.draw_rectangle(48,48,52,52,color);
    img3.draw_rectangle(98,98,102,102,color);

    CImgList<double> list1( img1.normalize(0,255),
                           img1.get_fft_modulo().normalize(0,255),
                           img1.get_fft_fase().normalize(0,255),
                           img1.get_fft_modulo_log().normalize(0,255) );
    list1.display(disp);
    disp.set_title("imagen original - modulo - fase - modulo log");

    CImgList<double> list2( img2.normalize(0,255),
                           img2.get_fft_modulo().normalize(0,255),
                           img2.get_fft_fase().normalize(0,255),
                           img2.get_fft_modulo_log().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("imagen original - modulo - fase - modulo log");

    CImgList<double> list( img3.normalize(0,255),
                           img3.get_fft_modulo().normalize(0,255),
                           img3.get_fft_fase().normalize(0,255),
                           img3.get_fft_modulo_log().normalize(0,255) );
    list.display(disp3);
    disp3.set_title("imagen original - modulo - fase - modulo log");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
