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
    
    CImg<double> img ( filename ), n4, n8;
    img.channel(0);
    img.display(disp);

    n4 = img.get_convolve( masks::laplaciano_n4() );
    n4.normalize(0,255).display(disp2);
    disp2.set_title("laplaciano n4");

    n8 = img.get_convolve( masks::laplaciano_n8() );
    n8.normalize(0,255).display(disp3);
    disp3.set_title("laplaciano n8");

    (n4+n8).normalize(0,255).display(disp4);
    disp4.set_title("laplaciano n4 + n8");

    n4.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp5 );
    disp5.set_title("laplaciano n4 - aplicación de umbral");

    n8.normalize(0,255).get_threshold( umbral ).normalize(0,255).display( disp6 );
    disp6.set_title("laplaciano n8 - aplicación de umbral");

    (n4 + n8).normalize(0,255).get_threshold( umbral ).display( disp7 );
    disp7.set_title("laplaciano n4 + n8 - aplicación de umbral");

    CImgList<double> list3 ( masks::laplaciano_n4().resize(100,100),
                             masks::laplaciano_n8().resize(100,100) );
    list3.display(disp8);
    disp8.set_title("masks laplaciano: n4 - n8");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
