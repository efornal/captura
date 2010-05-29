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

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img(400,400,1,1,0), 
        hough_dir ,hough_fil,
        hough_fil1, hough_fil2, hough_fil3, hough_fil4;

    // puntos blanco de la imagen
    img(0,0)     = 1;
    img(399,0)   = 1;
    img(0,399)   = 1;
    img(399,399) = 1;
    img(199,199) = 1;

    img.display(disp);
    
    hough_dir = hough_directa( img, dtita, dro, getHist); 

    hough_fil  = hough_dir.get_threshold( hough_dir.max() );
    hough_fil1 = hough_dir.get_threshold( hough_dir.max()-1 );
    hough_fil2 = hough_dir.get_threshold( hough_dir.max()-2 );

    hough_fil.display(disp1);
    hough_inversa( hough_fil ).display( disp2 );

    hough_fil1.display(disp3);
    hough_inversa( hough_fil1 ).display( disp4 );

    hough_fil2.display(disp4);
    hough_inversa( hough_fil2 ).display( disp5 );

    disp1.set_title("hough directa - umbral Max()");
    disp2.set_title("hough inversa - punto Max()");

    disp3.set_title("hough directa - umbral Max()-1");
    disp4.set_title("hough inversa - punto Max()-1");

    disp5.set_title("hough directa - umbral Max()-2");
    disp6.set_title("hough inversa - punto Max()-2");

    hough_dir.display("hough directa - 5 puntos");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
