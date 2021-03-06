#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/bone.tif",
                                         "ruta archivo imagen" );
    int x_inicial     = cimg_option ( "-x" ,   200, "valor x inicial" );
    int y_inicial     = cimg_option ( "-y" ,   200, "valor y inicial" );
    double tolerancia = cimg_option ( "-tol" , 40.0, "tolerancia en intencidad" );
    int vecinos       = cimg_option ( "-v" , 4, "cantidad vecinos (4-8)" );

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

	if ( disp.button() ) {
            x_inicial = disp.mouse_x();
            y_inicial = disp.mouse_y();
            printf( "punto: (%d,%d) \n",  disp.mouse_x(), disp.mouse_y() );
            segmentada_binaria = segmentar_binario ( img, x_inicial, y_inicial, 
                                                     tolerancia, vecinos );
            segmentada_binaria.display(disp1);
            segmentada_original = binaria_a_grises( segmentada_binaria, img );
            segmentada_original.display(disp2);
        }
        if ( disp.is_keyPAGEUP() ) { 
            vecinos = ( vecinos == 4 ) ?  8 : 4;

            segmentada_binaria = segmentar_binario ( img, x_inicial, y_inicial, 
                                                     tolerancia, vecinos );
            segmentada_binaria.display(disp1);
            segmentada_original = binaria_a_grises( segmentada_binaria, img );
            segmentada_original.display(disp2);

            printf( "vecinos: %d \n", vecinos );
        }
	if ( disp.is_keyARROWUP() ) {
            tolerancia++;

            segmentada_binaria = segmentar_binario ( img, x_inicial, y_inicial, 
                                                     tolerancia, vecinos );
            segmentada_binaria.display(disp1);
            segmentada_original = binaria_a_grises( segmentada_binaria, img );
            segmentada_original.display(disp2);

            printf( "tolerancia: %d \n", tolerancia );
	}
	if ( disp.is_keyARROWDOWN()) {
            tolerancia--;

            segmentada_binaria = segmentar_binario ( img, x_inicial, y_inicial, 
                                                     tolerancia, vecinos );
            segmentada_binaria.display(disp1);
            segmentada_original = binaria_a_grises( segmentada_binaria, img );
            segmentada_original.display(disp2);

            printf( "tolerancia: %d \n", tolerancia );
        }


    }
    return 0;
}
