#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );
    int umbral = cimg_option( "-u", 127, "umbral" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;
    
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

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();

        if (  disp.is_keyARROWDOWN() ) {
            umbral--;
            gx.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp5 );
            gy.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp6 );
            (gx + gy).normalize(0,255).get_threshold( umbral ).display( disp7 );
        } else if (  disp.is_keyARROWUP() ) {
            umbral++;
            gx.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp5 );
            gy.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp6 );
            (gx + gy).normalize(0,255).get_threshold( umbral ).display( disp7 );
        }

    }
    return 0;
}
