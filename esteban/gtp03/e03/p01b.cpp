/**
 * Variasiones de tamaño de filtrados promediadores
 * al aumentar el tamaño, se hace un mayor suavizado a la imagen
 * NOTA:
 * tener en cuenta que al convolucionar la mascara con la imagen
 * lo que estamos haciendo es aplicar el filtro en frecuencia.
 */

#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    CImgDisplay disp, disp2, disp3, disp4, disp5;
    CImg<float> img( filename ), img_3x3, img_5x5, img_10x10, img_20x20;

    img.display(disp);
    disp.set_title("imagen original");

    img_3x3 = img.get_convolve( masks::promedio(3,3) );
    img_3x3.print("mask 3x3");
    img_3x3.normalize(0,255).display(disp2);
    disp2.set_title("filtro con mask 3x3");

    img_5x5 = img.get_convolve( masks::promedio(5,5) );
    img_5x5.print("mask 5x5");
    img_5x5.normalize(0,255).display(disp3);
    disp3.set_title("filtro con mask 5x5");

    img_10x10 = img.get_convolve( masks::promedio(10,10) );
    img_10x10.print("img 10x10");
    img_10x10.normalize(0,255).display(disp4);
    disp4.set_title("filtro con mask 10x10");

    img_20x20 = img.get_convolve( masks::promedio(20,20) );
    img_20x20.print("img 20x20");
    img_20x20.normalize(0,255).display(disp5);
    disp5.set_title("filtro con mask 20x20");

    masks::promedio(3,3).normalize(0,255).display("mask 3x3");
    masks::promedio(5,5).normalize(0,255).display("mask 5x5");
    masks::promedio(10,10).normalize(0,255).display("mask 10x10");
    masks::promedio(20,20).normalize(0,255).display("mask 20x20");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { wait(); }
    return 0;
}
