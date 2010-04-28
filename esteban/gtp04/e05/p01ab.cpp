/**
 * El equalizado por canal separadamente  altera los colores
 * de la imagen original: debido a que la intencidad(brillo)
 * no esta separadas del tono(color) como en el HSI.
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/chairs_oscura.jpg", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ), 
        img_r( img.width(), img.height(), 1, 1, 0 ),
        img_g( img.width(), img.height(), 1, 1, 0 ),
        img_b( img.width(), img.height(), 1, 1, 0 ),
        view_r( img.width(), img.height(), 1, 3, 0 ),
        view_g( img.width(), img.height(), 1, 3, 0 ),
        view_b( img.width(), img.height(), 1, 3, 0 );
    CImgDisplay disp, disp2, disp3, disp4;

    img.get_resize(600,600).display(disp);
    disp.set_title("original");

    // separacion de canales
    cimg_forXY(img,x,y){
        img_r(x,y,0,0) = img(x,y,0,0);
        img_g(x,y,0,0) = img(x,y,0,1);
        img_b(x,y,0,0) = img(x,y,0,2);
    }

    // Lista canales rgb
        CImgList<double> rgb ( view_r.get_resize(200,200),
                               view_g.get_resize(200,200),
                               view_b.get_resize(200,200) );
    rgb.display(disp2);
    disp2.set_title("rojo - verde - azul (original)");

    //equalizado x canal
    img_r.equalize(255);
    img_g.equalize(255);
    img_b.equalize(255);

    // rejunte canales
    cimg_forXY(img,x,y){
        img(x,y,0,0) = img_r(x,y,0,0);
        img(x,y,0,1) = img_g(x,y,0,0);
        img(x,y,0,2) = img_b(x,y,0,0);
        view_r(x,y,0,0) = img(x,y,0,0);
        view_g(x,y,0,1) = img(x,y,0,1);
        view_b(x,y,0,2) = img(x,y,0,2);
    }

    //imagen equalizada
    img.get_resize(600,600).display(disp3);
    disp3.set_title("equalize R-G-B separados");

    // lista canales rgb equalizados
    CImgList<double> rgb_eq ( view_r.get_resize(200,200),
                              view_g.get_resize(200,200),
                              view_b.get_resize(200,200) );
    rgb_eq.display(disp4);
    disp4.set_title("rojo - verde - azul (equalizada)");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
