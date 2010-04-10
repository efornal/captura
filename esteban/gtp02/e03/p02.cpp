/**
 * Imagen.get_noise( variainza, tipo);
 * en los parámetros se especifica el tipo de ruido (gaussiano es el default) 
 * y la varianza. La media del ruido generado es cero. El ruido generado es aditivo.
 *
 * NOTA: con ./p02 -var 10 (varianza 10) se aprecia mejor
 *
 * FIXME: 
 * 1) la imagen promediada no sale muy bien!
 * 2) la media del ruido de la imagen original debe ser igual a la media del ruido
 *    de cualqueira de las imagenes Y/o a la media de la imagen promediada
 * 3) la suma entre imagenes debe promediarse siempre? 
 *    img1 + img2 = forxy{ img1(x,y)+img2(x,y) } / 2  ?
 *
 * POSTA:
 * para ver si la media del ruido es cero lo que tenes que hacer es sacar el
 * brillo medio de la imagen ( promedio de todos los pixels ) y desp le agregas
 * ruido haces de nuevo el proceso y te fijas si no cambia la media el ruido tiene
 * media cero
*/
#include <CImg.h>
#include <iostream>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );
    const int cantidad = cimg_option( "-n", 50 , 
                                        "cantidad de imagenes" );
    const double var = cimg_option( "-var", 0.05 , 
                                        "varianza" );

    CImg<double> img( filename );
    CImg<double> ruidosas[cantidad];
    CImg<double> promedio;

    CImgDisplay disp, disp2, disp3;

    img.display(disp); 
    cout << "Media de la imagen original: " << img.mean() << endl;

    disp.set_title("original");

    for( int i=0; i<cantidad; i++){
        ruidosas[i] = img.get_noise( var );
        //ruidosas[i].display(disp2);
        //sleep(1);
    }

    ruidosas[0].display(disp2);
    disp2.set_title("con ruido gausiano (ej: imagen uno)");


    promedio = ruidosas[0];
    cout << "Media de una de las imagenes con ruido: " << promedio.mean() << endl ;

    for( int i=1; i<cantidad; i++){
        promedio = sumar(promedio,ruidosas[i]);
    }
    cimg_forXY(promedio,x,y){
        promedio(x,y) = (promedio(x,y)/cantidad);
        //	reconstruida = sumar<CImg<float> > (reconstruida, imagen_sucia[i]);
    }
    promedio.display(disp3);
    disp3.set_title("promediada (suma todas / cantidad)");

    cout << "Media de la imagen promedio: " << promedio.mean() << endl 
         << "la media debe mantenerse." << endl;
 
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
