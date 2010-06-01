/**
 * (+-)45 => (+-) pi/4  =  (+-)0.78540
 * (+-)90 => (+-) pi/2  =  (+-)1.5708 
 *
 * bordes a 45:  ./p02b_theta -theta 0.78540
 * bordes a 90 (horizontales): ./p02b_theta -theta 1.5700 -umbral 1
 *
 * El maximo (en el plano p-o) de los puntos elegidos indica:
 *  - la recta donde mas puntos colineales hay en el plano x-y
 *  - la cantidad de puntos colineales en el plano x-y sobre esa recta
 *
 * si no hay una linea -importante- en el punto especificado, igual se
 * obtendran rectas pero que no seran de interes, estas tendran valores
 * maximos muy bajos (pocos punto colineales)
 * si el maximo es grande, indica una mayor cantidad de puntos y por lo
 * tanto puede ser la recta de interes.
 * Esto es subjetivo segun lo que se busque no...
 * => variando theta y rho se ve que los valores mas grandes da donde
 * hay lineas mas importantes
 *
 * FIXME: confirmar:
 * ./view_hough_param -f ../../imagenes/letras2.tif
 *     no es util si se tienen muchos objetos o lineas del mismo tamaño
 *     abria q hacer un filtrado con regiones eliminando los mas pequeños ?
 * ./view_hough_param -f ../../imagenes/snowman.png
 * a su vez, grandes bordes pueden dificultar los pequeños?
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
        img_po ,img_xy, img_hough_fil(img), 
        fil_color(img.width(), img.height(), 1,3,0 );
    img.channel(0);
    img.filtrar_sobel().normalize(0,255);
    img.display(disp);

    img_po = hough_directa( img ).normalize(0,255); 

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

        if (  disp.is_keyARROWDOWN() ) {
            theta-=tol_theta;
            printf("theta: %f \n",theta);
            goto calcula;

        } else if (  disp.is_keyARROWUP() ) {
            theta+=tol_theta;
            printf("theta: %f \n",theta);
            goto calcula;
        }
        if (  disp.is_keyARROWLEFT() ) {
            rho--;
            printf("rho: %f \n",rho);
            goto calcula;
        } else if (  disp.is_keyARROWRIGHT() ) {
            rho++;
            printf("rho: %f \n",rho);
            goto calcula;
        }
        if ( disp.is_keyPAGEDOWN() ){
            umbral--;
            printf("umbral: %f \n",umbral);
            goto calcula;
        } else if ( disp.is_keyPAGEUP() ) {
            umbral++;
            printf("umbral: %f \n",umbral);
            goto calcula;
        }

        goto saltar;
    calcula:
        img_hough_fil = filtrar_hough( img_po, rho, theta, tol_rho, tol_theta );
        printf("\t\t\t max: %f (cantidad puntos) \n", img_hough_fil.max() );
        
        img_hough_fil.display(disp4);
        img_hough_fil = get_solo_maximos( img_hough_fil, umbral );
        img_xy = hough_inversa( img_hough_fil );
        cimg_forXY(img,x,y){
            fil_color(x,y,0,0) = img_xy(x,y);
            fil_color(x,y,0,1) = img(x,y);
            fil_color(x,y,0,2) = img(x,y);
        }
        img_hough_fil.display(disp2);
        img_po.display(disp3);
        img_xy.display(disp1);
        fil_color.display(disp6);

    saltar:
        printf("");
    }
    return 0;
}
