#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    CImg<double> img ( filename ),img_hsi, img_rgb;
    // CImg<double> img_h(img.width(),img.height(),1,3,0);
    // CImg<double> img_s(img.width(),img.height(),1,3,0);
    // CImg<double> img_i(img.width(),img.height(),1,3,0);
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print();
    img_hsi = img.get_RGBtoHSI();

    cimg_forXY(img_hsi,x,y){
         img_hsi(x,y,0,0) =  y*(1/4096);
         cout<<     img_hsi(x,y,0,0)<<endl;
    }
    
    img_rgb = img_hsi.get_HSItoRGB();
    img_rgb.display(disp4);
    img_rgb.print();

    img_hsi.get_channel(0).print();
    img_hsi.get_channel(1).print();
    img_hsi.get_channel(2).print();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }

    return 0;
}
