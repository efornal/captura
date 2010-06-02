/**
 * distribucion de ruidos:
 * gaussiono        /                            \
 * uniforme                _-_-_
 * sal             |___
 * pimienta                 ___|
 * sal y pimienta   |___|
 */

#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/del-libro/original_pattern.tif",                                         "ruta archivo imagen" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );
    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;
    
    //TODO agregar otros tipos
    CHImg<double> img ( filename ),
        gaussiano (filename),
        uniforme (filename),
        sal (filename),
        pimienta (filename),
        sal_y_pimienta(filename);

    gaussiano.ruido_gaussiano( sigma );
    uniforme.ruido_uniforme( sigma );
    sal.ruido_sal( sigma );
    pimienta.ruido_pimienta( sigma );
    sal_y_pimienta.ruido_sal_y_pimienta( sigma );

    CImgList<double> list1( img,
                            gaussiano,
                            uniforme);

    CImgList<double> list2( sal,
                            pimienta,
                            sal_y_pimienta );

    list1.display(disp);
    disp.set_title("original - gaussiano - uniforme");

    list2.display(disp2);
    disp2.set_title("sal - pimienta - sal y pimienta");


    gaussiano.get_histogram(256,0,255).display_graph(disp3,3);
    uniforme.get_histogram(256,0,255).display_graph(disp4,3);
    sal.get_histogram(256,0,255).display_graph(disp5,3);
    pimienta.get_histogram(256,0,255).display_graph(disp6,3);
    sal_y_pimienta.get_histogram(256,0,255).display_graph(disp7,3);

    disp3.set_title("gaussiano");
    disp4.set_title("uniforme");
    disp5.set_title("sal");
    disp6.set_title("pimienta");
    disp7.set_title("sal y pimienta");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
