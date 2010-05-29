#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );
    double dtita = cimg_option( "-dtita", 1, "dtita" );
    double dro   = cimg_option( "-dro", 1, "dro" );
    bool getHist = cimg_option( "-hist", 0, "getHist" );
    int alto = 400, ancho = 400;

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img(ancho,alto,1,1,0), 
        img_po ,img_xy;

    img(0,0) = 1;

    img.display(disp);
    
    img_po = hough_directa( img, dtita, dro, getHist);
    img_xy = hough_inversa( img_po );

    img_po.display( disp1 );
    img_xy.display( disp2 );

    disp.set_title("punto en plano x-y");
    disp1.set_title("hough directa rho-theta");
    disp2.set_title("hough inversa x-y");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();

        if ( disp.is_event() 
             &&  disp.mouse_x() < ancho  &&  disp.mouse_y() < alto
             &&  disp.mouse_x() >= 0 &&  disp.mouse_y() >= 0 ) {

            img.fill(0);
            img( disp.mouse_x(), disp.mouse_y() ) = 1;

            img_po = hough_directa( img, dtita, dro, getHist);
            img_xy = hough_inversa( img_po );

            img.display( disp );
            img_po.display( disp1 );
            img_xy.display( disp2 );
        }

    }
    return 0;
}
