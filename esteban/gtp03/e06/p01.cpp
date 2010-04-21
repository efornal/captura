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

    img.alta_potencia( masks::suma_uno_medio(), 1 ).normalize(0,255).display(disp3);
    disp3.set_title("alta potencia");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }
    
    return 0;
}
