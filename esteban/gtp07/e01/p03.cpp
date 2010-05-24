#include <CHImg.h>
#include <masks.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/mosquito.jpg",
                                         "ruta archivo imagen" );
    int umbral = cimg_option( "-u", 127, "umbral" );
    double sigma1 = cimg_option( "-sigma1", 0.1, "varianza" );
    double sigma2 = cimg_option( "-sigma2", 5.0, "varianza" );
    double sigma3 = cimg_option( "-sigma3", 30.0, "varianza" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7, disp8;
    
    CHImg<double> img ( filename ), 
        img_gs1, img_gs2, img_gs3 ;
    img.channel(0);
    img.display(disp);

    // ruido gaussiano y varianza dada
    img_gs1 = img.get_noise(sigma1,0);
    img_gs2 = img.get_noise(sigma2,0);
    img_gs3 = img.get_noise(sigma3,0);

    CImgList<double> list ( img.get_filtrar_prewitt(), 
                            img_gs1.get_filtrar_prewitt(), 
                            img_gs2.get_filtrar_prewitt(), 
                            img_gs3.get_filtrar_prewitt() );
    list.display(disp3);
    disp3.set_title("prewitt: det.bordes con ruido - orig - sigma1 - sigma2 - sigma3");
    
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
