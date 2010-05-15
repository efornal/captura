/**
 * FIXME: comparativas ECM
 *  para ./p03 -f ../../imagenes/sangre.jpg
 *  ECM original-ruidosa: 305.04
 *  ECM original-filtrada geometica: 133.36
 *  ECM original-filtrada contra armonica: 239.44
 *
 *  para ./p03 -f ../../imagenes/camino.tif 
 *  ECM original-ruidosa: 971.295502
 *  ECM original-filtrada geometica: nan                ?????
 *  ECM original-filtrada contra armonica: 1272.403279
 *
 *  En general el filtrado contra armonico genera mas
 *  error entre la original y la filtrada ??? 
 *  al final donde es mejor el contra armonico ???
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
    CHImg<double> ruidosa ( img );
    
    ruidosa.ruido_sal_y_pimienta( sigma ).display(disp2);
    ruidosa.ruido_gaussiano( sigma ).display(disp3);

    ruidosa.get_filtrar_geometrica( n ).display(disp4);
    ruidosa.get_filtrar_contra_armonica( q, n ).display(disp5);
    
    disp.set_title("originial");
    disp2.set_title("original con sal y pimienta");
    disp3.set_title("original con sal y pimienta + ruido gaussiano");
    disp4.set_title("filtrado geometrico");
    disp5.set_title("filtrado contra armonica");

    printf("ECM original-ruidosa: %f\n", img.MSE( ruidosa ) );

    printf("ECM original-filtrada geometica: %f\n", 
           img.MSE( ruidosa.get_filtrar_geometrica( n ) ) );
    printf("ECM original-filtrada contra armonica: %f\n", 
           img.MSE( ruidosa.get_filtrar_contra_armonica( q, n ) ) );


    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
