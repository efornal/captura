#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/sangre.jpg",
                                         "ruta archivo imagen" );
    double n     = cimg_option("-n", 3.0 , "tamaño del filtro (nxn)" );
    double q     = cimg_option("-q", 1.0 , "orden del filtro contra-armonico" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> img ( filename ); //imagen gris
    img.channel(0);
    img.display(disp);

    CHImg<double> ruidosa (img.get_ruido_sal_y_pimienta( sigma ));
    ruidosa.display(disp2);
    ruidosa.ruido_gaussiano( sigma );
    ruidosa.display(disp3);

    ruidosa.get_filtrar_geometrica( n ).display(disp4);
    ruidosa.get_filtrar_contra_armonica( q, n ).display(disp5);
    
    disp.set_title("originial");
    disp2.set_title("original con ruido gaussiano");
    disp3.set_title("original con ruido gaussiano + sal y pimienta");
    disp4.set_title("filtrado geometrico");
    disp5.set_title("filtrado contra armonica");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        if ( disp.is_keyARROWDOWN () ){
            sigma -= 1; printf("sigma: %f\n", sigma);
        }
        if ( disp.is_keyARROWUP () ){
            sigma += 1; printf("sigma: %f\n", sigma);
        }

        if ( disp.is_keyARROWLEFT  () ) { 
            q--; printf("q (orden contra arm.): %f\n", q); 
        }
        if ( disp.is_keyARROWRIGHT () ) { 
            q++; printf("q (orden contra arm.): %f\n", q); 
        }

        if ( disp.is_keyPAGEUP()   ) { 
            n--; printf("n (size mask): %f\n", n); 
        }
        if ( disp.is_keyPAGEDOWN() ) { 
            n++; printf("n (size mask): %f\n", n); 
        }

        if ( disp.is_event() ) {
            ruidosa = img.get_ruido_sal_y_pimienta( sigma );
            ruidosa.display(disp2);
            ruidosa.ruido_gaussiano( sigma );
            ruidosa.display(disp3);

            ruidosa.get_filtrar_geometrica( n ).display(disp4);
            ruidosa.get_filtrar_contra_armonica( q, n ).display(disp5);
        }

    }
    return 0;
}
