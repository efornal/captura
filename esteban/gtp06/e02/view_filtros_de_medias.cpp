#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/del-libro/letras1.tif",
                                         "ruta archivo imagen" );
    double n     = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    double q     = cimg_option("-q", 1 , "orden del filtro contra-armonico" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);

    img.ruido_sal_y_pimienta( sigma ).display(disp2);
    img.ruido_gaussiano( sigma ).display(disp3);

    img.get_filtrar_aritmetica().display(disp4);
    img.get_filtrar_geometrica( n ).display(disp5);
    img.get_filtrar_armonica().display(disp6);
    img.get_filtrar_contra_armonica( q, n ).display(disp7);
    
    disp.set_title("originial");
    disp2.set_title("sal y pimienta");
    disp3.set_title("sal y pimienta + gaussiano");
    disp4.set_title("filtrado aritmetica");
    disp5.set_title("filtrado geometrica");
    disp6.set_title("filtrado armonica");
    disp7.set_title("filtrado contra armonica");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
