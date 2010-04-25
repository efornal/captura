/**
 * En comparacion con la original, el equalizado en el modelo HSI
 * es mejor, permite afectar solo el brillo(intensidad) de la imagen
 * sin afectar el color
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/chairs_oscura.jpg", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ), 
        img_original("../../imagenes/chairs.jpg"),
        img_hsi,
        img_h( img.width(), img.height(), 1, 1, 0 ),
        img_s( img.width(), img.height(), 1, 1, 0 ),
        img_i( img.width(), img.height(), 1, 1, 0 );
    CImgDisplay disp, disp2, disp3, disp4, disp5;

    img.get_resize(600,600).display(disp);
    disp.set_title("original oscura");

    img_hsi = img.get_RGBtoHSI();

    // separacion de canales
    cimg_forXY(img,x,y){
        img_h(x,y) = img_hsi(x,y,0,0);
        img_s(x,y) = img_hsi(x,y,0,1);
        img_i(x,y) = img_hsi(x,y,0,2);
    }

    // lista canales hsi
    CImgList<double> hsi ( img_h.get_resize(400,400).normalize(0,255),
                           img_s.get_resize(400,400).normalize(0,255),
                           img_i.get_resize(400,400).normalize(0,255) );
    hsi.display(disp2);
    disp2.set_title("(original)");

    //equalizado x canal (solo intensidad- brillo)
    img_i.equalize(255);

    // rejunte canales
    cimg_forXY(img_hsi,x,y){
        //img_hsi(x,y,0,0) = img_h(x,y);
        //img_hsi(x,y,0,1) = img_s(x,y);
        img_hsi(x,y,0,2) = img_i(x,y);
    }

    //imagen equalizada
    img_hsi.get_HSItoRGB().get_resize(600,600).display(disp3);
    disp3.set_title("RGB, con equalize mediante H-S-I (solo I)");

    img_original.get_resize(600,600).display(disp5);
    disp5.set_title("original clara, como deberia quedar");

    // lista canales rgb equalizados
    CImgList<double> hsi_eq ( img_h.get_resize(400,400).normalize(0,255),
                              img_s.get_resize(400,400).normalize(0,255),
                              img_i.get_resize(400,400).normalize(0,255) );
    hsi_eq.display(disp4);
    disp4.set_title(" (equalizada)");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
