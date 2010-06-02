/**
 * Estimacion por observacion de la imagen
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *orig = cimg_option( "-f",
                                        "../../imagenes/del-libro/lib-orig.tif",
                                         "ruta archivo imagen" );
    const char *noise = cimg_option( "-g",
                                        "../../imagenes/del-libro/lib-noise.tif",
                                         "ruta archivo imagen" );
    const char *sub_orig = cimg_option( "-subf",
                                        "../../imagenes/del-libro/lib-sub-orig.tif",
                                         "ruta archivo imagen" );
    const char *sub_noise = cimg_option( "-subg",
                                        "../../imagenes/del-libro/lib-sub-noise.tif",
                                         "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4, disp5;
    
    CHImg<double> original( orig ), ruidosa( noise ), 
        f ( sub_orig ), g( sub_noise ), 
        F, G, H(f), restaurada, h;

    f.channel(0);
    g.channel(0);
    CImgList<double> list1 ( f, g );
    list1.display(disp);
    
    F = f.get_fft_modulo();
    G = g.get_fft_modulo();

    // obtencion de funcion de degradacion:
    cimg_forXY(F,x,y){
        H(x,y) = G(x,y)/F(x,y);
    }
    
    restaurada = original.get_filtrada( H ); // H es menor, mal!!
    //sin embargo ya anda ...

    ruidosa.display(disp5);
    restaurada.display(disp4);
    original.display(disp3);

    disp.set_title("sub-img original, sub-img ruidosa");
    disp3.set_title("imagen original sin ruido");
    disp5.set_title("imagen con ruido");
    disp4.set_title("Imagen restaurada");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
