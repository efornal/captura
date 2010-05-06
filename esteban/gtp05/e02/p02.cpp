/**
 * FIXME porque superpone dos copias de una misma imagen ???
*/
#include <CHImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f1", "../../imagenes/letras1.tif", 
                                        "ruta archivo imagen" );
    const char *filename2 = cimg_option( "-f2", "../../imagenes/letras2.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<unsigned char> img1 ( filename1 ),
        img2 ( filename2 );

    CImgList<double> list1( img1.normalize(0,255),
                            img1.get_fft_modulo().normalize(0,255),
                            img1.get_fft_fase().normalize(0,255),
                            img1.get_fft_modulo_log().normalize(0,255) );
    list1.display(disp);
    disp.set_title("img1 - modulo - fase - modulo log");

    CImgList<double> list2( img2.normalize(0,255),
                            img2.get_fft_modulo().normalize(0,255),
                            img2.get_fft_fase().normalize(0,255),
                            img2.get_fft_modulo_log().normalize(0,255) );
    list2.display(disp3);
    disp3.set_title("img2 - modulo - fase - modulo log");


    CImgList<double> tdf1 = img1.get_FFT(false),
        tdf2 = img2.get_FFT(false);

    CImgList<double> list3( img1.get_a_fase_definida( tdf2[1] ),
                            img2.get_a_fase_definida( tdf1[1] ));

    list3.display(disp4);
    disp4.set_title("img1 con fase de img2 - img2 con fase de img1");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
