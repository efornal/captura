#include <CImg.h>

using namespace cimg_library;

namespace filtro {


    // ============================================================
    //                     Pasa Bajos
    // ============================================================

    /**
     * retorna un filtro PB Gaussiano con frecuencia de corte en wc
     */
    CImg<double> pb_gaussiano( int width=1, int height=1, double sigma=0.01 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0; //distancia de cada punto al origen
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            filtro(x,y) =  exp( -(distancia*distancia) / (2*sigma*sigma) );
        }
        return filtro;
    }

    /**
     * retorna un filtro PB Gaussiano con frecuencia de corte en wc
     */
    CImg<double> pb_gaussiano( CImg<double> img, double sigma=0.01 ) {
        return filtro::pb_gaussiano( img.width(), img.height(), sigma );
    }

    /**
     * retorna un filtro PB Butterworth con frecuencia de corte en wc
     * @orden : orden del filtro
     */
    CImg<double> pb_butter( int width=1, int height=1, int wc=1, int orden=1 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0; //distancia de cada punto al origen
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            filtro(x,y) =  1.0 / ( 1.0 + pow(distancia/wc, 2.0*orden) );
        }

        return filtro;
    }

    /**
     * retorna un filtro PB Butterworth con frecuencia de corte en wc
     */
    CImg<double> pb_butter( CImg<double> img, int wc=1, int orden=1 ) {
        return filtro::pb_butter( img.width(), img.height(), wc, orden );
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


    // ============================================================
    //                     Pasa Altos
    // ============================================================

    /**
     * retorna un filtro PA Gaussiano con frecuencia de corte en wc
     */
    CImg<double> pa_gaussiano( int width=1, int height=1, double sigma=0.01 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0; //distancia de cada punto al origen
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            filtro(x,y) =  1 - exp( -(distancia*distancia) / (2*sigma*sigma) );
        }
        return filtro;
    }

    /**
     * retorna un filtro PA Gaussiano con frecuencia de corte en wc
     */
    CImg<double> pa_gaussiano( CImg<double> img, double sigma=0.01 ) {
        return filtro::pa_gaussiano( img.width(), img.height(), sigma );
    }

    /**
     * retorna un filtro PA Butterworth con frecuencia de corte en wc
     * @orden : orden del filtro
     */
    CImg<double> pa_butter( int width=1, int height=1, int wc=1, int orden=1 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0; //distancia de cada punto al origen
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            filtro(x,y) =  1.0 / ( 1.0 + pow(wc/distancia, 2.0*orden) );
        }

        return filtro;
    }

    /**
     * retorna un filtro PA Butterworth con frecuencia de corte en wc
     */
    CImg<double> pa_butter( CImg<double> img, int wc=1, int orden=1 ) {
        return filtro::pa_butter( img.width(), img.height(), wc, orden );
    }

    /**
     * retorna un filtro PA ideal con frecuencia de corte en wc
     * a Cte sumada al filtro en la banda de paso,  
     * si a > 0 => agrega brillo medio
     */
    CImg<double> pa_ideal( int width=1, int height=1, int wc=1, double a=0.0) {

        double color[] = { 0.0+a, 0.0+a, 0.0+a };
        CImg<double> filtro ( width, height, 1, 1, 1 );
        filtro.draw_circle( width/2, height/2, wc, color );

        return filtro;
    }

    /**
     * retorna un filtro PA ideal con frecuencia de corte en wc
     */
    CImg<double> pa_ideal( CImg<double> img, int wc=1, double a=0.0 ) {
        return filtro::pa_ideal( img.width(), img.height(), wc, a );
    }


    // ============================================================
    //                     Rechaza Banda
    // ============================================================

    /**
     * retorna un filtro RB (rechaza banda) ideal
     */
    CImg<double> rb_ideal( int width=1, int height=1, int wc=1, int ancho=1 ) {

        double rechazo[] = { 0.0, 0.0, 0.0};
        double paso[]    = { 1.0, 1.0, 1.0};
        float angulo = 0.0;
        CImg<double> filtro ( width, height, 1, 1, 1 );

        filtro.draw_circle( width/2, height/2, wc+ancho/2, rechazo );
        filtro.draw_circle( width/2, height/2, wc-ancho/2, paso );

        return filtro;
    }

    // ============================================================
    //                     Homomorfico
    // ============================================================

    /**
     * retorna un filtro Homomorfico
     * Debe filtrarse con get_filtrado_homomorfico(filtro)
     * por defecto gh=1, gl=0 => pasaaltos normalizado
     * 1-) genero un PA con wc y orden dados
     * 2-) normalizo entre los valor gl y gh
     */
    CImg<double> homomorfico( CImg<double> img, 
                              double wc=1.0, 
                              double gl=0.0,
                              double gh=1.0,
                              int orden=1) {
        CImg<double> filtro = filtro::pa_butter( img, wc, orden );
        return filtro.normalize(gl,gh);
    }


}
