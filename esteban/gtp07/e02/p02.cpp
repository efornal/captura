#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/letras1.tif",
                                         "ruta archivo imagen" );
    double theta = cimg_option( "-theta", M_PI/4.0, "valor de angulo" );
    double rho   = cimg_option( "-rho", 1.0, "valor de radio" );
    double tol_theta = cimg_option( "-tol_theta", 0.1, "tolerancia  angulo" );
    double tol_rho   = cimg_option( "-tol_rho", 0.1, "tolerancia radio" );
    double umbral    = cimg_option( "-umbral", 100, "umbral puntos" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CHImg<double> img( filename ), 
        img_po ,img_xy, img_hough_fil(img), test(img);
    img.channel(0);
    img.filtrar_sobel().normalize(0,255);
    img.display(disp);
    test.fill(0.0);
    
    img_po = hough_directa( img ); 
    
    img_hough_fil = filtrar_hough_theta( img_po, theta, tol_theta );
    img_hough_fil = get_solo_maximos( img_hough_fil, 100 ).display();
    img_xy = hough_inversa( img_hough_fil );

    img_hough_fil.display(disp2);
    img_po.display(disp3);
    img_xy.display(disp1);

    disp.set_title("xy - original");
    disp1.set_title("xy - original filtrada");
    disp2.set_title("po - hough filtrada");
    disp3.set_title("po - hough sin filtrar");
    img_po.display();
    img_hough_fil.display();
    filtrar_hough_theta( test, theta, tol_theta ).normalize(0,255).display("test");
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
