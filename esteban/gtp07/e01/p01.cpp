#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );
    int umbral = cimg_option( "-u", 127, "umbral" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7, disp8;
    
    CImg<double> img ( filename ), gx, gy;
    img.channel(0);
    img.display(disp);

    gx = img.get_convolve( masks::roberts_gx() );
    gx.normalize(0,255).display(disp2);
    disp2.set_title("deteccion de bordes: roberts gx");

    gy = img.get_convolve( masks::roberts_gy() );
    gy.normalize(0,255).display(disp3);
    disp3.set_title("deteccion de bordes: roberts gy");

    (gx+gy).normalize(0,255).display(disp4);
    disp4.set_title("deteccion de bordes: roberts gx + gy");

    gx.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp5 );
    disp5.set_title("deteccion de bordes: roberts gx - aplicación de umbral");

    gy.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp6 );
    disp6.set_title("deteccion de bordes: roberts gy - aplicación de umbral");

    (gx + gy).normalize(0,255).get_threshold( umbral ).display( disp7 );
    disp7.set_title("deteccion de bordes: roberts gx + gy - aplicación de umbral");

    CImgList<double> list3 ( masks::roberts_gx().resize(100,100),
                             masks::roberts_gy().resize(100,100) );
    list3.display(disp8);
    disp8.set_title("masks roberts: gx - gy");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
