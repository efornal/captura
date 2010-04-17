#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    double var = cimg_option( "-var", 1,"varianza" );
    int n = cimg_option( "-n", 3,"n valores para la mscara: nxn" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename ),g( masks::gaussiana(n,n,var) );
    
    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::gaussiana(n,n,var) ).normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada con mask gaussiana");

    masks::gaussiana(n,n,var).normalize(0,255).display("mask gaussiana");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
