/**
 * FIXME: es mejor filtrar en brillo HSI que en RGB?
 * no se nota mucha  diferencia  ??
*/
#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/camino.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ), 
        img_hsi,
        img_h( img.width(), img.height(), 1, 1, 0 ),
        img_s( img.width(), img.height(), 1, 1, 0 ),
        img_i( img.width(), img.height(), 1, 1, 0 );
    CImgDisplay disp, disp2, disp3, disp4, disp5;

    img.display(disp);
    disp.set_title("original");

    img_hsi = img.get_RGBtoHSI();

    // separacion de canales
    cimg_forXY(img,x,y){
        img_h(x,y) = img_hsi(x,y,0,0);
        img_s(x,y) = img_hsi(x,y,0,1);
        img_i(x,y) = img_hsi(x,y,0,2);
    }

    // lista canales hsi
    CImgList<double> hsi ( img_h.get_resize(200,200).normalize(0,255),
                           img_s.get_resize(200,200).normalize(0,255),
                           img_i.get_resize(200,200).normalize(0,255) );
    hsi.display(disp2);
    disp2.set_title("(original)");

    //filtrado x canal (solo intensidad- brillo)
    img_i.convolve( masks::suma_uno_medio() );

    // rejunte canales
    cimg_forXY(img_hsi,x,y){
        //img_hsi(x,y,0,0) = img_h(x,y);
        //img_hsi(x,y,0,1) = img_s(x,y);
        img_hsi(x,y,0,2) = img_i(x,y);
    }

    //imagen equalizada
    img_hsi.get_HSItoRGB().display(disp3);
    disp3.set_title("RGB, con filtrado mediante H-S-I (solo I)");

    // lista canales rgb equalizados
    CImgList<double> hsi_eq ( img_h.get_resize(200,200).normalize(0,255),
                              img_s.get_resize(200,200).normalize(0,255),
                              img_i.get_resize(200,200).normalize(0,255) );
    hsi_eq.display(disp4);
    disp4.set_title(" (filtrada)");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
