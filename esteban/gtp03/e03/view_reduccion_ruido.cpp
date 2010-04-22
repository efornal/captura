#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    const double varianza = cimg_option( "-var", 10 , 
                                    "varianza" );
    const double k = cimg_option( "-k", (1.0/25) , 
                                    "factor k del filtro (k*mask)" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename );
    //    img.channel(0);
    img.display(disp);
    disp.set_title("imagen original");

    CImg<double> img_ruido ( img.get_noise( varianza ) );
    img_ruido.display(disp2);
    disp2.set_title("imagen con ruido");

    img_ruido.get_convolve( masks::promedio(5,5,k) ).normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada con mask 5x5, k=1/25, reducción de ruido");

    masks::promedio(5,5,k).normalize(0,255).display("mask prom ruido");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
