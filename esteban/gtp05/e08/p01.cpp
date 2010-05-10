/**
 * FIXME: esta bien el calculo de la funcion de transf. del filtro
 * Hap (alta_potencia) alculado asi: ?
 * 1-) a partir de un filtro P Altos espacial gaussiano hpa(x,y), obtenemos 
 *     Hpa(u,v) = IFFT{ hpa(x,y) }
 * 2-) luego obtenemos el Hap (alta potencia) mediante:
 *     Hap(u,v) = (A-1) + Hpa(u,v)
 * 3-) Aplicamos el filtro: 
 *     filtrada = g(x,y) = IFFT{ F(u,v).Hap(u,v) }    correcto ??
 *
 * TODO: hacer q funcione para img que no son cuadradas
*/
#include <CHImg.h>
#include <iostream>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/hand.tif", 
                                        "ruta archivo imagen" );
    double sigma = cimg_option( "-sigma", 0.1, "varianza del filtro gaussiano" );
    double a = cimg_option( "-a", 1.0, "a, CTE filtro Alta Potencia a>=1" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<double> img ( filename );

    CHImg<double> mask = masks::pa_gaussian( img.width(), sigma );
    CHImg<double> Hpa = mask.get_fft_modulo();
    CHImg<double> Hap(Hpa);

    // obtengo filtro alta potencia
    cimg_forXY(Hpa,x,y){
        Hap(x,y) = (a-1.0) + Hpa(x,y);
    }

    CImgList<double> list1( img.get_normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    list1.display(disp);
    disp.set_title("imagen original - modulo log - fase");

    CImgList<double> list2( Hap.get_normalize(0,255),
                            Hap.get_fft_modulo_log().normalize(0,255),
                            Hap.get_fft_fase().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("filtro - modulo log - fase");

    CHImg<double> filtrada = img.get_filtrada( Hap );
    
    CImgList<double> list5( filtrada.get_normalize(0,255),
                            filtrada.get_fft_modulo_log().normalize(0,255),
                            filtrada.get_fft_fase().normalize(0,255) );
    list5.display(disp5);
    disp5.set_title("filtrada: modulo - modulo log - fase");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
