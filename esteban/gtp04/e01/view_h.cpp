#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/patron.tif", 
                                        "ruta archivo imagen" );

    int h_grados = cimg_option( "-h", 0,"valor de h en grados" );

    CImg<double> img ( filename ),img_hsi, img_rgb;
    // CImg<double> img_h(img.width(),img.height(),1,3,0);
    // CImg<double> img_s(img.width(),img.height(),1,3,0);
    // CImg<double> img_i(img.width(),img.height(),1,3,0);
    CImgDisplay disp, disp2, disp3, disp4;

    img.display(disp); 
    img.print("RGB");

    disp.set_title("img original");
    img_hsi = img.get_RGBtoHSI();
    img_hsi.print("HSI");

    cimg_forXY(img_hsi,x,y){
        img_hsi(x,y,0,0) =  img_hsi(x,y,0,0) + h_grados;
         cout<<     img_hsi(x,y,0,0)<<endl;
    }
    
    img_rgb = img_hsi.get_HSItoRGB();
    img_rgb.display(disp4);
    disp4.set_title("img modificada");
    // img_rgb.print();

    // img_hsi.get_channel(0).print();
    // img_hsi.get_channel(1).print();
    // img_hsi.get_channel(2).print();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();

        
        if ( disp.is_keyARROWUP () ){
            h_grados+=1;

    cimg_forXY(img_hsi,x,y){
        img_hsi(x,y,0,0) =  img_hsi(x,y,0,0) + h_grados;
    }
    
    img_rgb = img_hsi.get_HSItoRGB();
    img_rgb.display(disp4);

            printf("h: %d \n",h_grados);
        }

        if ( disp.is_keyARROWDOWN () ){
            h_grados-=1;

    cimg_forXY(img_hsi,x,y){
        img_hsi(x,y,0,0) =  img_hsi(x,y,0,0) + h_grados;
    }
    
    img_rgb = img_hsi.get_HSItoRGB();
    img_rgb.display(disp4);

            printf("h: %d \n",h_grados);
        }
    }

    return 0;
}
