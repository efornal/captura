/**
 * Con funcion variable se aprecia mejor los cambios
*/
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );
    CImg<double> img ( filename );
    //CImg<double> img ( 300, 300,1, 3, 100); usando img cte
    CImg<double> img_hsi, img_rgb;
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print("RGB");

    disp.set_title("img original");
    img_hsi = img.get_RGBtoHSI();
    img_hsi.print("HSI");

    double w = img_hsi.width();
    double m = 1.0/w;
    cimg_forXY(img_hsi,x,y){
        img_hsi(x,y,0,2) =  m*(x-w) + 1;
    }

    img_rgb = img_hsi.get_HSItoRGB();
    img_rgb.display("i = 1 CTE(max brillo)");

    img_hsi.get_channel(2).display("i = 1 CTE");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
