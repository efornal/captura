#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/estanbul.tif",
                                         "ruta archivo imagen" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CImg<double> img(400,400,1,1,0), 
        img_po ,img_po_fil,
        img_po_fil1, img_po_fil2, img_po_fil3, img_po_fil4;

    // puntos blanco de la imagen
    img(0,0)     = 1;
    img(399,0)   = 1;
    img(0,399)   = 1;
    img(399,399) = 1;
    img(199,199) = 1;

    img.display(disp);
    
    img_po = hough_directa( img ); 

    img_po_fil  = img_po.get_threshold( img_po.max() );
    img_po_fil1 = img_po.get_threshold( img_po.max()-1 );
    img_po_fil2 = img_po.get_threshold( img_po.max()-2 );

    img_po_fil.display(disp1);
    hough_inversa( img_po_fil ).display( disp2 );

    img_po_fil1.display(disp3);
    hough_inversa( img_po_fil1 ).display( disp4 );

    img_po_fil2.display(disp4);
    hough_inversa( img_po_fil2 ).display( disp5 );

    disp1.set_title("po - hough directa - umbral Max()");
    disp2.set_title("xy - hough inversa - punto Max()");

    disp3.set_title("po - hough directa - umbral Max()-1");
    disp4.set_title("xy - hough inversa - punto Max()-1");

    disp5.set_title("po - hough directa - umbral Max()-2");
    disp6.set_title("xy - hough inversa - punto Max()-2");

    img_po.display("plano po - hough directa - 5 puntos");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
