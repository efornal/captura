/**
 * El alfa recordado da un ECM bajo respecto de las otras
 * y la imagen tiene un buen aspecto
 *
 * ECM original-ruidosa: 301.610682
 * ECM original-filtrada (mediana y pto medio): 212.373339
 * ECM original-filtrada (alfa recortado): 55.936329

 * incluso si la imagen tiene un sigma alto:
 * ./p02 -d 8 -sigma 10
 * con un valor alto de d, quita bastante bien el ruido
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/sangre.jpg",
                                         "ruta archivo imagen" );
    int n = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    int d = cimg_option("-d", 0 , "orden del filtro alfa recortado [0 a mn-1]" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);
    CHImg<double> ruidosa ( img ), mediana_y_pto_medio, alfa_recortado;
    
    ruidosa.ruido_sal_y_pimienta( sigma ).display(disp2);
    ruidosa.ruido_gaussiano( sigma ).display(disp3);

    mediana_y_pto_medio = ((CHImg<double>)ruidosa.get_filtrar_mediana(n)).
        get_filtrar_punto_medio( n );
    mediana_y_pto_medio.display(disp4);

    alfa_recortado = ruidosa.get_filtrar_alfa_recortado( d, n );
    alfa_recortado.display(disp5);

    disp.set_title("originial");
    disp2.set_title("original con sal y pimienta");
    disp3.set_title("original con sal y pimienta + ruido gaussiano");
    disp4.set_title("filtrado mediana y punto medio");
    disp5.set_title("filtrado alfa recortado");

    printf("ECM original-ruidosa: %f\n", img.MSE( ruidosa ) );

    printf("ECM original-filtrada (mediana y pto medio): %f\n", 
           img.MSE( mediana_y_pto_medio ) );
    printf("ECM original-filtrada (alfa recortado): %f\n", 
           img.MSE( alfa_recortado ) );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
