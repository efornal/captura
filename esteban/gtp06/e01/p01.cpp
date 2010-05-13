/**
 * noice: Add random noise to the values of the instance image.
 *
 * Parameters:
 *   - sigma      Amplitude of the random additive noise. 
 *                If sigma<0, it stands for a percentage of the global value range.
 *
 *   - noise_type Type of additive noise 
 *                0 = gaussian, 
 *                1 = uniform, 
 *                2 = Salt and Pepper, 
 *                3 = Poisson 
 *                4 = Rician
 */

#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/del_libro/vertical_rectangle_gris.png",                                         "ruta archivo imagen" );
    double sigma = cimg_option("-sigma", 0.1 , "amplitud del ruido" );
    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    //TODO agregar otros tipos
    CHImg<double> img ( filename ),
        gaussiano (img),
        uniforme (img),
        sal_y_pimienta(img);

    gaussiano.noise( sigma, 0 );
    uniforme.noise( sigma, 1 );
    sal_y_pimienta.noise( sigma, 2 );

    CImgList<double> list1( img,
                            gaussiano,
                            uniforme,
                            sal_y_pimienta );
    list1.display(disp);
    disp.set_title("original - gaussiano - uniforme - sal-pimienta");

    gaussiano.get_histogram(255).display_graph(disp2,3);
    uniforme.get_histogram(150,255).display_graph(disp3,3);
    sal_y_pimienta.get_histogram(255).display_graph(disp4,3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
