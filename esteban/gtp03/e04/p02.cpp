/**
 * Preguunta: que umbral seria el adecuado? la media, u otro?
 * POSTA: la media no nos da un indicador para esto,
 * una opcion mas adecuada seria ver el histograma y en base a eso
 * evaluar el umbral, pero el proceso es manual, no automatizado.
*/
#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/hubble.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename );
    
    img.display(disp);
    disp.set_title("imagen original");

    CImg<double> img_fil = img.get_convolve( masks::promedio() );
    img_fil.normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada PB promediador");

    img_fil.print("img_fil");

    img_fil.get_threshold(img_fil.mean()).display(disp3);
    disp3.set_title("imagen filtrada PB promediador + threshold");

    img.get_threshold(img_fil.mean()).display(disp4);
    disp4.set_title("imagen + threshold, sin filtro");

    masks::promedio().normalize(0,255).display("mask promedio");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
