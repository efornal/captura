/**
 *   FIXME: no funciona la mascara no se como se usa!!
*/
#include <CHImg.h>
#include <masks.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../imagenes/ej7a.tif", 
                                        "ruta archivo imagen" );

    CImgDisplay disp, disp2, disp3, disp4,disp5;
    CHImg<double> img( filename ),mask(3,3),dest(img.width(),img.height(),1,255);
    //    img.channel(0);
    img.display(disp);
    disp.set_title("imagen original");
    /*
CImg<unsigned char> src("image_color.jpg"), dest(src,false), neighbor(5,5);  // Image definitions.
  typedef unsigned char uchar;             // Avoid space in the second parameter of the macro CImg_5x5x1 below.
  CImg<> N(5,5);                           // Define a 5x5 neighborhood as a 5x5 image.
  cimg_forC(src,k)                         // Standard loop on color channels
     cimg_for5x5(src,x,y,0,k,N,float)      // 5x5 neighborhood loop.
       dest(x,y,k) = N.sum()/(5*5);        // Averaging pixels to filter the color image.
  CImgList<unsigned char> visu(src,dest);
  visu.display("Original + Filtered");     // Display both original and filtered image.
    */
    cimg_forC(img,k){
        cimg_for5x5( img, x, y, 0, k, mask, double ){
            //            dest[x,y,k] = mask.get_equalize(255)[x,y,k];
            dest[x,y,k] = mask[x,y,k];
        }
    }
    mask.display(disp3);
    dest.display(disp4);
    dest.normalize(0,255).display(disp5);
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) { 
        disp.wait();
    }

    return 0;
}
