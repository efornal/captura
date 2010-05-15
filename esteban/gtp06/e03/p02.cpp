
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/sangre.jpg",
                                         "ruta archivo imagen" );
    int n        = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    double q     = cimg_option("-q", 1 , "orden del filtro contra-armonico" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);
    CHImg<double> ruidosa ( img );
    
    ruidosa.ruido_sal_y_pimienta( sigma ).display(disp2);
    ruidosa.ruido_gaussiano( sigma ).display(disp3);

    ruidosa.get_filtrar_mediana(n).display(disp4);
    ruidosa.get_filtrar_punto_medio( n ).display(disp5);

    disp.set_title("originial");
    disp2.set_title("original con sal y pimienta");
    disp3.set_title("original con sal y pimienta + ruido gaussiano");
    disp4.set_title("filtrado mediana");
    disp5.set_title("filtrado pto. medio");

    // printf("ECM original-ruidosa: %f\n", img.MSE( ruidosa ) );

    // printf("ECM original-filtrada geometica: %f\n", 
    //        img.MSE( ruidosa.get_filtrar_geometrica( n ) ) );
    // printf("ECM original-filtrada contra armonica: %f\n", 
    //        img.MSE( ruidosa.get_filtrar_contra_armonica( q, n ) ) );


    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
