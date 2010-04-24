/**
 * HSI - variacion componente h [0-360] pero aca en [0-240]
 * esta imagen varia en sus valores de 0-240(angulo) RGB (ver triang colores)
 * por tanto se visualiza como un degrade de 0 a 240
 *
 * HSI - variacion componente s [0-1]
 * esta imagen es de un color omogeneo (CTE) debido que para todos
 * los colores del degrade anterior, tiene la misma saturacion
 *
 * HSI - variacion componente i [0-1]
 * la intencidad varia segun la mezcla de las 3 componenetes(en este caso)
 * 
*/
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    const int h = cimg_option( "-h", 0,"valor de h en grados" );

    CImg<double> img ( filename ),img_hsi, img_rgb;
    CImg<double> img_h(img.width(),img.height(),1,3,0);
    CImg<double> img_s(img.width(),img.height(),1,3,0);
    CImg<double> img_i(img.width(),img.height(),1,3,0);
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print("RGB");

    disp.set_title("img original");
    img_hsi = img.get_RGBtoHSI();
    img_hsi.print("HSI");

    cimg_forXY(img_hsi,x,y){
        img_h(x,y,0,0) =  img_hsi(x,y,0,0);
        img_s(x,y,0,1) =  img_hsi(x,y,0,1);
        img_i(x,y,0,2) =  img_hsi(x,y,0,2);
    }
    
    img_rgb = img_hsi.get_HSItoRGB();
    img_h.normalize(0,255).display("HSI - variacion componente h");
    img_s.normalize(0,255).display("HSI - variacion componente s");
    img_i.normalize(0,255).display("HSI - variacion componente i");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
