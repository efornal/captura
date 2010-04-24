/**
 * Des histograma se puede decir que el inervalo para el negro (color del rio)
 * esta mas o menos de 0-20
 * 
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/rio.jpg", 
                                        "ruta archivo imagen" );
    int umbral =cimg_option("-u", 20,"umbral de corte color rio [0->umbral]");

    CHImg<double> img ( filename ), rgb( img.width(), img.height(), 1, 3);

    CImgDisplay disp, disp2, disp3, disp4;
    img.display(disp);
    disp.set_title("imagen original");

    cimg_forXY(img,x,y){
        if ( img(x,y) > umbral ) {
            rgb(x,y,0,0) = img(x,y); // rojo
            rgb(x,y,0,1) = img(x,y); // verde
            rgb(x,y,0,2) = img(x,y); // azul
        } else {
            rgb(x,y,0,0) = 255; // rojo
            rgb(x,y,0,1) = 255; // verde
            rgb(x,y,0,2) = 0.0; // sin azul      => amarillo
        }
    }
    rgb.display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
