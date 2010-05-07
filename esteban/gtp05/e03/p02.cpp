#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/huang2.jpg", 
                                        "ruta archivo imagen" );
    int fc = cimg_option( "-fc", 100, "frecuencia de corte" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img ( filename ),
        filtro ( img.width(), img.height(), 1, 1, 0 );
    unsigned char color[] = {1,1,1};

    filtro.draw_circle( img.width()/2, img.height()/2, fc, color );
    filtro.shift( filtro.width()/2, filtro.height()/2, 0, 0, 2 );    

    CImgList<double> list1( img.normalize(0,255),
                            img.get_fft_modulo_log().normalize(0,255) );
    list1.display(disp);
    disp.set_title("imagen original - modulo log");

    CImgList<double> list3( img.get_fft_modulo().normalize(0,255),
                            img.get_fft_fase().normalize(0,255) );
    list3.display(disp3);
    disp3.set_title("img original: modulo - fase");

    CImgList<double> list2( filtro.normalize(0,255),
                            filtro.get_fft_modulo_log().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("filtro - modulo log");

    CImgList<double> list4( filtro.get_fft_modulo().normalize(0,255),
                            filtro.get_fft_fase().normalize(0,255) );
    list4.display(disp4);
    disp4.set_title("filtro: modulo - fase");

    CImgList<double> tdf = img.get_FFT();
    cimg_forXY(filtro,x,y){
        tdf[0](x,y) *= filtro(x,y);
        tdf[1](x,y) *= filtro(x,y);
    }
    
    CHImg<double> img_fil = tdf.get_FFT(true)[0];
    img_fil.display();
    img_fil.get_fft_modulo().log().normalize(0,255).display();
    CImgList<double> list5( img_fil.get_fft_modulo().normalize(0,255),
                            img_fil.get_fft_fase().normalize(0,255),
                            img_fil.get_fft_modulo_log().normalize(0,255) );
    list5.display(disp5);
    disp5.set_title("filtrada: modulo - fase");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
