/**
 * FIXME: que umbral seria el adecuado? la media, u otro?
 * que ventajas tengo de usar umbral con y sin pre-filtrado(suavizado)
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
    //img_fil.normalize(0,255).display(disp2);
    //disp2.set_title("imagen filtrada PB promediador");

    img_fil.print("img_fil");

    img_fil.get_threshold(img_fil.mean()).display(disp3);
    disp3.set_title("imagen filtrada PB promediador + threshold");

    img.get_threshold(img_fil.mean()).display(disp4);
    disp4.set_title("imagen + threshold, sin filtro");

    masks::promedio().normalize(0,255).display("mask promedio");

    double umbral = img_fil.mean();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();

        if ( disp.is_keyARROWUP () ){
            ++umbral;
            img_fil.get_threshold( umbral ).display(disp3);
            img.get_threshold( umbral ).display(disp4);
            printf("umbral: %f \n",umbral);
        }

        if ( disp.is_keyARROWDOWN () ){
            --umbral;
            img_fil.get_threshold( umbral ).display(disp3);
            img.get_threshold( umbral ).display(disp4);
            printf("umbral: %f \n",umbral);
        }

    }
    
    return 0;
}
