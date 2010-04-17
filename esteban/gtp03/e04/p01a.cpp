#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename ),g( masks::gaussiano3x3());

    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::gaussiano3x3() ).normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada con mask gausseana");

    masks::gaussiano3x3().normalize(0,255).display("mask gausseana");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
