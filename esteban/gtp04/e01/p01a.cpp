/**
 * FIXME confirmar:
 * Dado que rotar los valores de h mediante una suma o resta
 * de angulo, no se puede llegar cd RGB a BGR, no se puede hacer
 * la transformacion mediante suma o resta de angulo (ademas 
 * habria que tener en cuenta no pasarse de 240 grados)
 * a) partiendo de R-y-G-c-B(0-240º) sumando  180 obtenemos BRG
 * b) partiendo de R-y-G-c-B(0-240º) restando 180 obtenemos GBR
 * en ambos casos se considera que si pasa de 240 comienza en cero!
 * la opcion que queda es invertir valores el R<->B
*/

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    const int h = cimg_option( "-h", 0,"valor de h en grados" );

    CImg<double> img ( filename ),img_hsi, img_rgb, aux;
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print("RGB");

    disp.set_title("img original");
    img_hsi = img.get_RGBtoHSI();
    aux = img_hsi;
    img_hsi.print("HSI");

    //inversion de valores
    cimg_forXY(img_hsi,x,y){
        aux(x,y,0,0) =  img_hsi( img_hsi.width()-x-1, y, 0, 0);
    }
    
    img_rgb = aux.get_HSItoRGB();
    img_rgb.display(disp4);
    disp4.set_title("img h invertida");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
