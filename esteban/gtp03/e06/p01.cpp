#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/estanbul.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CHImg<double> img( filename );
    
    img.display(disp);
    disp.set_title("imagen original");

    img.get_mascara_difusa( masks::promedio(3,3), 1 ).normalize(0,255).display(disp3);
    disp3.set_title("mascara difusa");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }
    
    return 0;
}
