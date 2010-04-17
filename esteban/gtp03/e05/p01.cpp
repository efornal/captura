/**
 * FIXME: conclusión correcta???
 * para las mascaras con valor central alto (9) y negativos no tanto (-1)
 * deja pasar variaciones altas filtrando un poco las bajas
 *
 * para las mascaras con valor central medio (5) y negativo (-2) mas altos
 * deja pasar variaciones medias altas filtrando un poco mas las bajas
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

    img.get_convolve( masks::suma_uno_bajo() ).normalize(0,255).display(disp2);
    disp2.set_title("imagen filtrada PA: suma uno bajo");

    img.get_convolve( masks::suma_uno_medio() ).normalize(0,255).display(disp3);
    disp3.set_title("imagen filtrada PA: suma uno medio");

    img.get_convolve( masks::suma_uno_alto() ).normalize(0,255).display(disp4);
    disp4.set_title("imagen filtrada PA: suma uno alto");

    masks::suma_uno_bajo().normalize(0,255).display("mask suma uno bajo");
    masks::suma_uno_medio().normalize(0,255).display("mask suma uno medio");
    masks::suma_uno_alto().normalize(0,255).display("mask suma uno alto");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }
    
    return 0;
}
