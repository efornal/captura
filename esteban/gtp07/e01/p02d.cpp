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
    
    CImg<double> img ( filename ), LoG;
    img.channel(0);
    img.display(disp);

    LoG = img.get_convolve( masks::laplaciano_g() );
    LoG.normalize(0,255).display(disp2);
    disp2.set_title("laplaciano del gaussiano");

    LoG.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp5 );
    disp5.set_title("laplaciano del gaussiano - aplicación de umbral");

    masks::laplaciano_g().resize(100,100).display(disp8);
    disp8.set_title("masks laplaciano del gaussiano");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
