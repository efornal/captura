/**
 * FIXME: no da la mismo , no funciona el cero padding!!??
 */
#include <CHImg.h>
#include <iostream>
#include <filtro.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f1", "../../imagenes/patron2_min.tif", 
                                        "ruta archivo imagen" );
    const char *filename2 = cimg_option( "-f2", "../../imagenes/letras1_min.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;

    CHImg<double> f ( filename1 ), h ( filename2 ) ;

    CHImg<double> g = f.get_convolve( h );
    //CHImg<double> g = ( h );

    f.print("f");
    h.print("h");
    g.print("g");

    CImgList<double> list1( f.get_normalize(0,255),
                            f.get_fft_modulo_log().normalize(0,255),
                            f.get_fft_fase().normalize(0,255) );
    list1.display(disp);
    disp.set_title("f - modulo log - fase");

    CImgList<double> list2( h.get_normalize(0,255),
                            h.get_fft_modulo_log().normalize(0,255),
                            h.get_fft_fase().normalize(0,255) );
    list2.display(disp2);
    disp2.set_title("h - modulo log - fase");
 
    CImgList<double> list3( g.get_normalize(0,255),
                            g.get_fft_modulo_log().normalize(0,255),
                            g.get_fft_fase().normalize(0,255) );
    list3.display(disp3);
    disp3.set_title("g=f*h - modulo log - fase");


    // CHImg<double> tdfF = f.get_FFT()[0];
    // CHImg<double> tdfH = h.get_FFT()[0];
    // CHImg<double> Fz( f.width()*2-1, f.height()*2-1, 1, 1, 0 ); //TODO : tomar la mayor
    // CHImg<double> Hz( h.width()*2-1, h.height()*2-1, 1, 1, 0 );//TODO : tomar la mayor
    // CImgList<double> tdfG( tdfF,tdfF );

    // cimg_forXY(tdfF,x,y){
    //     Fz(x,y) = tdfF(x,y);
    // }
    // cimg_forXY(tdfH,x,y){
    //     Hz(x,y) = tdfH(x,y);
    // }
    // Hz.get_normalize(0,255).display("Hz");
    // Fz.get_normalize(0,255).display("Fz");
    // cimg_forXY(Hz,x,y){
    //     tdfG[0](x,y) = Hz(x,y)*Fz(x,y);
    //     tdfG[1](x,y) = 0.0; //fase nula
    // }

    CImgList<double> tdfF = f.get_FFT();
    CImgList<double> tdfH = h.get_FFT();
    CImg<double> tpl1 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImg<double> tpl2 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImg<double> tpl3 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImg<double> tpl4 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImg<double> tpl5 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImg<double> tpl6 (f.width()*2-1, f.height()*2-1, 1, 1, 0);
    CImgList<double> Fz( tpl1,tpl2 ); //TODO : tomar la mayor
    CImgList<double> Hz( tpl4,tpl3 );//TODO : tomar la mayor
    CImgList<double> tdfG( tpl5,tpl6 );

    cimg_forXY(tdfF[0],x,y){
        Fz[0](x,y) = tdfF[0](x,y);
        Fz[1](x,y) = tdfF[1](x,y);
    }
    cimg_forXY(tdfH[0],x,y){
        Hz[0](x,y) = tdfH[0](x,y);
        Hz[1](x,y) = tdfH[1](x,y);
    }
    //    Hz.get_normalize(0,255).display("Hz");
    // Fz.get_normalize(0,255).display("Fz");
    Hz[0].print("hz 0");
    Fz[0].print("fz 0");
    tdfG[0].print("gz 0");
    tdfG[1].print("gz 1");
    cimg_forXY(Hz[0],x,y){
        tdfG[0](x,y) = Hz[0](x,y)*Fz[0](x,y);
        tdfG[1](x,y) = Hz[1](x,y)*Fz[1](x,y);
    }

    CHImg<double> g2 = tdfG.get_FFT(true)[0];

    CImgList<double> list4( g2.get_normalize(0,255),
                            g2.get_fft_modulo_log().normalize(0,255),
                            g2.get_fft_fase().normalize(0,255) );
    list4.display(disp4);
    disp4.set_title("g2=ITDF{Fz*Hz} - modulo log - fase");


    //    tdfG.get_FFT(true)[0].normalize(0,255).display(disp5);
    // g.normalize(0,255).display(disp4);
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
