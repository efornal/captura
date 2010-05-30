#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/bone.tif",
                                         "ruta archivo imagen" );
    int x_inicial  = cimg_option ( "-x" ,   200, "valor x inicial" );
    int y_inicial  = cimg_option ( "-y" ,   200, "valor y inicial" );
    int tolerancia = cimg_option ( "-tol" , 40.0, "tolerancia en intencidad" );
    int vecinos    = cimg_option ( "-v" , 4, "cantidad vecinos (4-8)" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img( filename ), 
        segmentada_binaria, segmentada_original;
    
    img.display(disp);
    disp.set_title("original");
                                   
    segmentada_binaria = segmentar_binario ( img, x_inicial, y_inicial, 
                                             tolerancia, vecinos );
    segmentada_binaria.display(disp1);

    segmentada_original = binaria_a_grises( segmentada_binaria, img );
    segmentada_original.display(disp2);

    disp1.set_title("segmentada binaria");
    disp2.set_title("segmentada escala grises");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
