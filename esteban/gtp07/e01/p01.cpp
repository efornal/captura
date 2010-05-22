#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CImg<double> img ( filename ), gx, gy;

    img.display(disp);

    gx = img.get_convolve( masks::roberts_gx() );
    gx.normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada: roberts gx");

    gy = img.get_convolve( masks::roberts_gy() );
    gy.normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada: roberts gy");


    (gx+gy).normalize(0,255).display(disp4);
    disp4.set_title("imagen filtrada: roberts gx + gy");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
