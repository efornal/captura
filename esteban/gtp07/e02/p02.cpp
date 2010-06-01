/**
 * (+-)45 => (+-) pi/4  =  (+-)0.78540
 * (+-)90 => (+-) pi/2  =  (+-)1.5708 
 *
 * bordes a 45:  ./p02b_theta -theta 0.78540
 * bordes a 90 (horizontales): ./p02b_theta -theta 1.5700 -umbral 1
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/letras1.tif",
                                         "ruta archivo imagen" );
    double rho = cimg_option( "-rho", 100, "valor de modulo" );
    double tol_rho = cimg_option( "-tol_rho", 1.0, "tolerancia al modulo" );
    double theta = cimg_option( "-theta", 0.78540, "valor de angulo" );
    double tol_theta = cimg_option( "-tol_theta", 0.01, "tolerancia al angulo" );
    double umbral    = cimg_option( "-umbral", 10, "umbral puntos" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CHImg<double> img( filename ), 
        img_po ,img_xy, img_hough_fil(img);
    img.channel(0);
    img.filtrar_sobel().normalize(0,255);
    img.display(disp);

    img_po = hough_directa( img ).normalize(0,255); 

    // cotas:
    //img_hough_fil = filtrar_hough_rho( img_po, rho, tol_rho );
    //img_hough_fil = filtrar_hough_rho_max( img_po, rho );
    //img_hough_fil = filtrar_hough_rho_min( img_po, rho );
    img_hough_fil = filtrar_hough( img_po, rho, theta, tol_rho, tol_theta );


    img_hough_fil.display(disp4);
    img_hough_fil = get_solo_maximos( img_hough_fil, umbral );
    img_xy = hough_inversa( img_hough_fil );

    img_hough_fil.display(disp2);
    img_po.display(disp3);
    img_xy.display(disp1);

    disp.set_title("xy - original");
    disp1.set_title("xy - original filtrada");
    disp2.set_title("po - ptos elegidos");
    disp3.set_title("po - hough sin filtrar");
    disp4.set_title("po - ptos para rho");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
