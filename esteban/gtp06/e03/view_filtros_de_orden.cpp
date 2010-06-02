#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/letras1.tif",
                                         "ruta archivo imagen" );
    int n = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    int d = cimg_option("-d", 0 , "orden del filtro alfa recortado [0 a mn-1]" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7, disp8, disp9;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);

    img.ruido_sal_y_pimienta( sigma ).display(disp2);
    img.ruido_gaussiano( sigma ).display(disp3);

    img.get_filtrar_mediana().display(disp4);
    // img.get_filtrar_moda().display(disp5); FALTA, usar mediana es similar
    img.get_filtrar_max().display(disp6);
    img.get_filtrar_min().display(disp7);
    img.get_filtrar_punto_medio().display(disp8);
    img.get_filtrar_alfa_recortado(d).display(disp9);
    
    disp.set_title("originial");
    disp2.set_title("sal y pimienta");
    disp3.set_title("sal y pimienta + gaussiano");
    disp4.set_title("filtrado mediana");
    disp5.set_title("filtrado moda");
    disp6.set_title("filtrado max");
    disp7.set_title("filtrado min");
    disp8.set_title("filtrado pto medio");
    disp9.set_title("filtrado alfa recortado");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
