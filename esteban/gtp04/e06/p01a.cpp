#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/futbol.jpg", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ); 
    CImgDisplay disp;

    img.display(disp);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
