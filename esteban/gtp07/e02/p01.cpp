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

    CImgDisplay disp, disp2, disp3, disp4;
    
    CImg<double> img ( filename ), hough_dir, hough_inv;
    img.channel(0);
    img.display(disp);
    
    hough_dir = hough_directa( img, dtita, dro, getHist); 

    hough_inv = hough_inversa( img ); 

    hough_dir.normalize(0,255).display();
    hough_inv.normalize(0,255).display();

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
