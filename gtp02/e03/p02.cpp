/**
   FIXME: como se genera una imagen con media 0, varianza 0.05??
   deberia funcionar con la imagen: a7v600-X(RImpulsivo).gif?
*/
#include <CImg.h>
#include <operaciones.h>

using namespace cimg_library;
using namespace std;

//CImg<unsigned char> ruido( CImg<unsigned char> img ){
//    CImg<unsigned char> img1( dx, dy, 1, 1 );
//}

int main( int argc, char **argv ) {
    const char *filename1 = cimg_option( "-f", "../../imagenes/a7v600-X(RImpulsivo).gif", 
                                        "ruta archivo imagen 1" );

    CImg<unsigned char> img1( filename1 );

    CImgDisplay disp, disp2, disp3;

    //img1.draw_gaussian (50,50,img1,color,1);

    img1.display(disp);

    view_promedio(img1,5,disp3);

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) 
            && (!disp2.is_closed() &&  !disp2.is_keyQ())) {}
    return 0;
}
