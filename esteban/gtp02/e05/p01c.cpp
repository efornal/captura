/**
   FIXME: esta bien hecho asi? y para que esto?
*/
#include <CImg.h>
#include <artisticos.h>

using namespace cimg_library;
using namespace std;

/**
   binariza la imagen en un intervalo para un determinado valor
*/
CImg<unsigned char> get_umbral( CImg<unsigned char> img, 
                                int min, 
                                int max, 
                                int valor){
    cimg_forXY( img, x, y ){
        if ( img(x,y) > min && img(x,y) < max ) {
            if ( img(x,y) > valor ) {
                img(x,y) = 1;
            } else {
                img(x,y) = 0;
            }
        }
    }
    return img;
} 

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    CImg<unsigned char> img1( filename1 );
    
    CImgDisplay disp, disp2, disp3;

    img1.display(disp);
    get_umbral( get_umbral( get_umbral( img1, 0, 100, 50 ),
                            101, 200, 150 )
                ,201,255,225).display("binaria por intervalos");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
