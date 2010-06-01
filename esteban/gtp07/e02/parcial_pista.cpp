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
                                        "../../imagenes/corrientes_ruidogris.jpg",
                                         "ruta archivo imagen" );
    double rho = cimg_option( "-rho", 100, "valor de modulo" );
    double tol_rho = cimg_option( "-tol_rho", 1.0, "tolerancia al modulo" );
    double theta = cimg_option( "-theta", 0.78540, "valor de angulo" );
    double tol_theta = cimg_option( "-tol_theta", 0.01, "tolerancia al angulo" );
    double umbral    = cimg_option( "-umbral", 10, "umbral puntos" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CHImg<double> img( filename ), 
        img_po ,img_xy, fil_theta, fil_rho, 
        fil_theta_ptos, img_xy_ptos, img_xy_theta, fil_theta_mas_rho, fil_ptos;
    img.channel(0);
    img.filtrar_sobel().normalize(0,255);
    img.display(disp);

    img_po = hough_directa( img ).normalize(0,255); 


    fil_theta = filtrar_hough_theta( img_po, theta, tol_theta );
    fil_theta_mas_rho = filtrar_hough_rho_max( fil_theta, rho );
    //img_hough_fil = filtrar_hough_rho_min( img_po, rho );
    //img_hough_fil = filtrar_hough( img_po, rho, theta, tol_rho, tol_theta );

    fil_theta_ptos = get_solo_maximos( fil_theta, umbral );
    fil_ptos = get_solo_maximos( fil_theta_mas_rho, umbral );
    img_xy_theta = hough_inversa( fil_theta_ptos );
    img_xy = hough_inversa( fil_ptos );


    img_po.display(disp1);
    fil_theta.display(disp2);
    img_xy_theta.display(disp3);
    fil_theta_mas_rho.display(disp4);
    img_xy.display(disp5);

    disp.set_title("xy - original");


    disp1.set_title("po - hough sin filtrar");
    disp2.set_title("po - filtrado theta");
    disp3.set_title("xy - solo theta");
    disp4.set_title("po - filtrado theta+rho");
    disp5.set_title("xy - theta + rho");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
