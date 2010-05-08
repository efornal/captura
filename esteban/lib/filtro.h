#include <CImg.h>

using namespace cimg_library;

namespace filtro {

    /**
     * retorna un filtro PB Butterworth con frecuencia de corte en wc
     */
    CImg<double> pb_butter( int width=1, int height=1, int wc=1 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0; //distancia de cada punto al origen
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            filtro(x,y) =  1.0 / (1.0 + (distancia/wc) );
        }

        return filtro;
    }

    /**
     * retorna un filtro PB Butterworth con frecuencia de corte en wc
     */
    CImg<double> pb_butter( CImg<double> img, int wc=1 ) {
        return filtro::pb_butter( img.width(), img.height(), wc );
    }

    /**
     * retorna un filtro PB ideal con frecuencia de corte en wc
     */
    CImg<double> pb_ideal( int width=1, int height=1, int wc=1 ) {

        unsigned char color[] = {1,1,1};
        CImg<double> filtro ( width, height, 1, 1, 0 );

        filtro.draw_circle( width/2, height/2, wc, color );

        return filtro;
    }

    /**
     * retorna un filtro PB ideal con frecuencia de corte en wc
     */
    CImg<double> pb_ideal( CImg<double> img, int wc=1 ) {
        return filtro::pb_ideal( img.width(), img.height(), wc );
    }

}
