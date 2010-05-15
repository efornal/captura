/**
 * FIXME : porque el contraarmonico generalmente da gris omogeneo ???
 * ver con:
 * ./p01 -f ../../imagenes/del-libro/original_pattern.tif -sigma 10
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

    CImgDisplay disp, disp2, disp3, disp4;
    
    CHImg<double> img ( filename ); //imagen gris
    img.display(disp);

    img.ruido_gaussiano( sigma ).display(disp2);

    img.get_filtrar_geometrica( n ).display(disp3);

    img.get_filtrar_contra_armonica( q, n ).display(disp4);
    
    disp.set_title("originial");
    disp2.set_title("original con ruido gaussiano");
    disp3.set_title("filtrado geometrico");
    disp4.set_title("filtrado contra armonica");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
