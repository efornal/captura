/**
 * FIXME: confirmar:
 * Con masks::suma_uno_alto()
 * mejora la definicion (o contraste?) pero los colores
 * estan como mas lavados, (saturados?)
 *
 * Con masks::suma_uno_bajo()
 * Bastante bien, mejora el contraste y hay/nohay perdida de colores
 *
 * Con masks::suma_uno_medio()
 * Bastante bien, probablemente el mejor de los 3 suma uno
 *
 * Con masks::suma_cero()
 * empeora!( se pierde todo el fondo)
*/

#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/camino.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ), 
        img_r( img.width(), img.height(), 1, 3, 0 ),
        img_g( img.width(), img.height(), 1, 3, 0 ),
        img_b( img.width(), img.height(), 1, 3, 0 );
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp);
    disp.set_title("original");

    // separacion de canales
    cimg_forXY(img,x,y){
        img_r(x,y,0,0) = img(x,y,0,0);
        img_g(x,y,0,1) = img(x,y,0,1);
        img_b(x,y,0,2) = img(x,y,0,2);
    }

    // lista canales rgb
    CImgList<double> rgb ( img_r.get_resize(200,200),
                           img_g.get_resize(200,200),
                           img_b.get_resize(200,200) );
    rgb.display(disp2);
    disp2.set_title("rojo - verde - azul (original)");

    // filtrado x canal
    img_r.convolve( masks::suma_uno_medio() );
    img_g.convolve( masks::suma_uno_medio() );
    img_b.convolve( masks::suma_uno_medio() );

    // rejunte canales
    cimg_forXY(img,x,y){
        img(x,y,0,0) = img_r(x,y,0,0);
        img(x,y,0,1) = img_g(x,y,0,1);
        img(x,y,0,2) = img_b(x,y,0,2);
    }

    //imagen filtrada
    img.display(disp3);
    disp3.set_title("filtrada R-G-B separados");

    // lista canales rgb filtrados
    CImgList<double> rgb_eq ( img_r.get_resize(200,200),
                              img_g.get_resize(200,200),
                              img_b.get_resize(200,200) );
    rgb_eq.display(disp4);
    disp4.set_title("rojo - verde - azul (filtrada)");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
