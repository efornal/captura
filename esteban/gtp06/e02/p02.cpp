/**
 * FIXME: filtrado contra armonico 
 * 1-) contra armonico bueno para ruido impulsivo, pero viendo la
 * imagen filtrada no parece ser muy bueno !??
 * 2-) no es lo mismo aplicar un ruido y luego otro !?
 * si aplico gaussiano sobre impulsivo no queda lo mismo
 * que aplicar impulsivo sobre gaussiano, cual primero? 
 *
 * ver:
 * ./p02 -f ../../imagenes/camino.tif
 * ./p02 -f ../../imagenes/del-libro/original_pattern.tif   ???
 *
 * filtrado geometrico
 *   + bueno ruido gaussiano
 *   - malo  ruido impulsivo
 *
 * filtrado contra armonico
 *   + bueno ruido impulsivo
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/sangre.jpg",
                                         "ruta archivo imagen" );
    double n     = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    double q     = cimg_option("-q", 1 , "orden del filtro contra-armonico" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);

    img.ruido_sal_y_pimienta( sigma ).display(disp3);
    img.ruido_gaussiano( sigma ).display(disp2);


    img.get_filtrar_geometrica( n ).display(disp4);

    img.get_filtrar_contra_armonica( q, n ).display(disp5);
    
    disp.set_title("originial");
    disp2.set_title("original con ruido gaussiano");
    disp3.set_title("original con ruido gaussiano + sal y pimienta");
    disp4.set_title("filtrado geometrico");
    disp5.set_title("filtrado contra armonica");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
