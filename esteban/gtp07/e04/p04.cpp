/**
 * ./p04 -x0 260 -y0 170 -r 50
 * ./p04 -x0 149 -y0 135 -r 50
*/
#include <CHImg.h>
#include <list>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/rosas.jpg",
                                         "ruta archivo imagen" );
    int x0     = cimg_option ( "-x0" ,   260, "valor x inicial" );
    int y0     = cimg_option ( "-y0" ,   170, "valor y inicial" );
    int radio  = cimg_option( "-r", 50, "radio de  tolerancia");
    int paleta  = cimg_option( "-p", 5, "color paleta");
    double k  = cimg_option( "-k", 1.0/9.0, "tolerancia del filtro");
    int size  = cimg_option( "-size", 3, "tama�o del filtro");

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img( filename );
    list<int> etiquetas; // tabla etiquetas
    
    img.display(disp);
    disp.set_title("original");
                            
    CImg<unsigned char> mask = gen_mascara_segmentacion_rgb( img, x0, y0, radio );

    CImg<double> mask_filtrada = mask.get_convolve( masks::promedio(size,size,k) );

    CImg<double> mask_labeled =  label_cc( mask_filtrada, etiquetas );

    mask.normalize(0,255).display(disp2);
    disp2.set_title("mascara segmentada RGB");

    mask_filtrada.normalize(0,255).display(disp3);
    disp3.set_title("mascara segmentada RGB - filtrada");

    mask_labeled.normalize(0,255).display(disp4);
    disp4.set_title("mascara segmentada RGB - filtrada - etiquetada");

    aplicar_paleta( mask_labeled, paleta ).display(disp5);
    disp5.set_title("mascara segmentada coloreada");

    printf ( "Cantidad de rosas: %d \n", cantidad_de_regiones( etiquetas ) );

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
