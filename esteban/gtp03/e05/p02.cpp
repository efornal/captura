/**
 * FIXME: cual es la diferencia ???
 * NOTA:
 * se compara con el suma uno alto, ya que es el mas parecido 
 * al suma cero, para detectar diferencias minimas
*/
#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/estanbul.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4;
    CImg<double> img( filename );
    
    img.display(disp);
    disp.set_title("imagen original");

    img.get_convolve( masks::suma_uno_alto() ).normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada PA: suma uno alto");

    img.get_convolve( masks::suma_cero() ).normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada PA: suma cero");

    masks::suma_uno_alto().normalize(0,255).display("mask suma uno alto");
    masks::suma_cero().normalize(0,255).display("mask suma cero");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }
    
    return 0;
}
