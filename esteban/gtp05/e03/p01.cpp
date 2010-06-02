/**
 * FIXME: en este hay que hacer todas la simg del mismo tamaño
 * e ir variando el tamaño del rectangulo
 * El ancho del filtro en frecuencia es inversamente
 * proporcional al mismo en tiempo!, no?
 * Por tanto: 
 * |           |
 * |-____  =>  |___._
 *  t              w
 *  
 * |           |
 * |----_  =>  |.___
 *    t         w
 *
 * cuadro pequeño => frec corte alta
 * cuadro grande  => frec corte baja
 */
#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img(filename), 
        img1 ( img.width(),img.height(),1,1,0 ),
        img2 ( img.width(),img.height(),1,1,0 ),
        img3 ( img.width(),img.height(),1,1,0 );
    unsigned char color[] = {255,255,255};

    img1.draw_rectangle(118,118,139,139,color);
    img2.draw_rectangle(78,78,178,178,color);
    img3.draw_rectangle(28,28,228,228,color);

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
