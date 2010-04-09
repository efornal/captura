/**
   Imagen.get_noise( variainza, tipo);
     en los parámetros se especifica el tipo de ruido (gaussiano es el default) 
     y la varianza. La media del ruido generado es cero. El ruido generado es aditivo.
     FIXME: la imagen promediada no sale bien!
*/
#include <CImg.h>
#include <iostream>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    const int cantidad = cimg_option( "-n", 10 , 
                                        "cantidad de imagenes" );
    const double var = cimg_option( "-var", 0.05 , 
                                        "varianza" );

    CImg<unsigned char> img( filename );
    CImg<unsigned char> ruidosas[cantidad];
    CImg<unsigned char> promedio;

    CImgDisplay disp, disp2, disp3;

    img.display(disp); 
    disp.set_title("original");
    disp2.set_title("con ruido gausiano");
    disp3.set_title("promediada");

    for( int i=0; i<cantidad; i++){
        ruidosas[i] = img.get_noise( var );
        //ruidosas[i].display(disp2);
        //sleep(1);
    }

    ruidosas[0].display(disp2);
    promedio = ruidosas[0];

    for( int i=1; i<cantidad; i++){
        promedio = suma(promedio,ruidosas[i]);
    }
    cimg_forXY(promedio,x,y){
        promedio(x,y) =promedio(x,y)/cantidad;
    }
    promedio.display(disp3);
 
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
