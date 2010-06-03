/**
 * Estimacion por observacion de la imagen
 * FIXME: ver forma de hacerlo abajo, estan bien??
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *orig = cimg_option( "-f",
                                        "../../imagenes/del-libro/lib-orig-400.tif",
                                         "ruta archivo imagen" );
    const char *noise = cimg_option( "-g",
                                        "../../imagenes/del-libro/lib-noise-400.tif",
                                         "ruta archivo imagen" );
    const char *sub_orig = cimg_option( "-subf",
                                        "../../imagenes/del-libro/lib-sub-orig_10.tif",
                                         "ruta archivo imagen" );
    const char *sub_noise = cimg_option( "-subg",
                                        "../../imagenes/del-libro/lib-sub-noise_10.tif",
                                         "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6;
    
    CHImg<double> original( orig ), ruidosa( noise ), 
        f ( sub_orig ), g( sub_noise ), 
        restaurada1, restaurada2, h;
    CImgList<double>  HH(original,original), F,G,H;
    f.channel(0);
    g.channel(0);
    CImgList<double> list1 ( f, g );
    list1.display(disp);
    
    F = f.get_FFT();
    G = g.get_FFT();

    F = realimag2magfase(F);
    G = realimag2magfase(G);

    //=============\
    // obtencion de funcion de degradacion:
    cimg_forXY(F[0],x,y){
        HH[0](x,y) = G[0](x,y)/F[0](x,y);
        HH[1](x,y) = G[0](x,y)/F[0](x,y); //fase lineal
    }

    HH = magfase2realimag ( HH );
    h = HH.get_FFT(true)[0];
    restaurada1=f;
    restaurada1 = ruidosa.get_convolve(h); //OJO PODE ESTAR UN MES!!
    //-------------/

    //=============\
    //2 forma restauracion: antes hay q hacer H del tamanio de F!
    //Es factible de esta forma??
    cimg_forXY(F[0],x,y){
        HH[0](x,y) = G[0](x,y)/F[0](x,y);
        HH[1](x,y) = G[0](x,y)/F[0](x,y); //fase lineal
    }

    restaurada2 = ruidosa.get_filtrada( H[0] ); // H es menor, mal!!
    //-------------/

    ruidosa.display(disp5);
    restaurada1.display(disp4);
    restaurada2.display(disp6);
    original.display(disp3);

    disp.set_title("sub-img original, sub-img ruidosa");
    disp3.set_title("imagen original sin ruido");
    disp5.set_title("imagen con ruido");
    disp4.set_title("Imagen restaurada 1");
    disp6.set_title("Imagen restaurada 2");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
