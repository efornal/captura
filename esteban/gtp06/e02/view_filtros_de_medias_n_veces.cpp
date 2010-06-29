#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/letras1.tif",
                                         "ruta archivo imagen" );
    double n     = cimg_option("-n", 3 , "tamaño del filtro (nxn)" );
    double veces     = cimg_option("-veces", 5 ,
                                   "numero veces q aplicamo el filtro" );
    double q     = cimg_option("-q", 1 , "orden del filtro contra-armonico" );
    double sigma = cimg_option("-sigma", 4.0 , "amplitud del ruido" );

    CImgDisplay disp, disp2, disp3, disp4, disp5, disp6, disp7;

    CHImg<double> img ( filename ), 
      img1(img), img2(img), img3(img), img4(img), img5(img); //imagen gris
    img.channel(0);
    img.display(disp);

    //    img.ruido_sal_y_pimienta( sigma ).display(disp2);
    //    img.ruido_gaussiano( sigma ).display(disp3);
    for (int u=0; u<veces; u++) {
      img1 = img1.get_filtrar_aritmetica();
      img2 = img2.get_filtrar_geometrica( n );
      img3 = img3.get_filtrar_armonica();
      img4 = img4.get_filtrar_contra_armonica( q, n );
    }
    img1.display(disp4);
    img2.display(disp5);
    img3.display(disp6);
    img4.display(disp7);

    disp.set_title("originial");
    disp4.set_title("filtrado aritmetica");
    disp5.set_title("filtrado geometrica");
    disp6.set_title("filtrado armonica");
    disp7.set_title("filtrado contra armonica");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait();
    }
    return 0;
}
