#include <CImg.h>

using namespace cimg_library;
using namespace std;

CImg<unsigned char> suma( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    return (img1 + img2) / 2;
}

/**
   Autosuma una imgaen n veces y la divide por n (promedio)
*/
CImg<unsigned char> promedio( CImg<unsigned char> img, int n=2 ) { 
    for (int i=0; i<n; i++) {
        img += img;
    }
    return img / n;
}

/**
   Autosuma una imgaen n veces y la divide por n (promedio)
   renderiza en display el proceso
*/
void view_promedio( CImg<unsigned char> img, int n, CImgDisplay disp ) { 
    for (int i=0; i<n; i++) {
        /*cimg_forXY(img,x,y){
            img(x,y) = (img(x,y) + img(x,y))/2;
            }*/
        img.display(disp);
        img += img;
        sleep(1);
    }
    (img / n).display(disp);
    sleep(2);
}

/**
   aplica una mascara a una imagen (multiplicacion)
*/
CImg<unsigned char> enmascarar( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    CImg<unsigned char> mascara( img1.width(), img1.height(), 1, 1);
    cimg_forXY(img1,x,y){
        mascara(x,y) = img1(x,y) * img2(x,y);
    }
    return mascara;
}

/**
   division entre imagenes
*/
CImg<unsigned char> division( CImg<unsigned char> img1, CImg<unsigned char> img2 ) { 
    CImg<unsigned char> result( img1.width(), img1.height(), 1, 1);
    cimg_forXY(img1,x,y){
        result(x,y) = img1(x,y) / img2(x,y);
    }
    return result;
}
