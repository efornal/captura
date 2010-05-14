/**
 * FIXME: histograma
 * 1-) porque en el histograma el gris 50 de la imagen
 * no aparece en la posicio 50 del histograma ??
 * 2-) cual es el efecto en el histograma de porciones de gris CTE??
 *
 * POSTA: el histograma debe graficarse con indicando los valores:
 * get_histogram( niveles, 0, niveles-1 )
 * ya que de lo contrario no incluye el cero (no se ve bien el histograma)
*/
#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );  
    int niveles = cimg_option("-niveles", 256 , "niveles en el histograma" );
    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;
    
    //TODO agregar otros tipos
    CHImg<double> img ( 200,200,1,1,50 ), //imagen gris
        gaussiano (img),
        uniforme (img),
        sal (img),
        pimienta (img),
        sal_y_pimienta(img);

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


    gaussiano.get_histogram(niveles,0,niveles-1).display_graph(disp3,3);
    uniforme.get_histogram(niveles,0,niveles-1).display_graph(disp4,3);
    sal.get_histogram(niveles,0,niveles-1).display_graph(disp5,3);
    pimienta.get_histogram(niveles,0,niveles-1).display_graph(disp6,3);
    sal_y_pimienta.get_histogram(niveles,0,niveles-1).display_graph(disp7,3);

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
