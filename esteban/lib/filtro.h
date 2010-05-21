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

    /**
     * retorna un filtro RB (rechaza banda) butterworth
     * formula:
     *                      1
     *   H(u,v) = ----------------------
     *            1 + [ D*W / D^2-wc^2 ]
     *
     * D  = distancia de cada punto al origen
     * wc = frecuencia de corte
     * W  = ancho del filtro
     * aux =  [ D*W / D^2-wc^2 ]
     */
    CImg<double> rb_butter( int width=1, int height=1, int wc=1, int ancho=1, int orden=1 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0.0, aux = 0.0;
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            aux = (ancho*distancia) / ( pow(distancia,2) - pow(wc,2) );
            filtro(x,y) =  1.0 / ( 1.0 + pow( aux, 2.0*orden) );
        }

        return filtro;
    }

    /**
     * retorna un filtro RB (rechaza banda) gaussiano
     * formula:
     *                  (-1/2) * [ D^2-wc^2 / DW  ]
     *   H(u,v) = 1 - e
     *            
     *
     * D  = distancia de cada punto al origen
     * wc = frecuencia de corte
     * W  = ancho del filtro
     * aux =   [ D^2-wc^2 / DW  ]
     */
    CImg<double> rb_gaussiano( int width=1, int height=1, int wc=1, int ancho=1 ) {

        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia = 0.0, aux = 0.0;
        int mediox = width/2, 
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia = sqrt ( pow(x-mediox,2.0) + pow(y-medioy,2.0) );
            aux = ( pow(distancia,2) - pow(wc,2) ) / ( distancia*ancho );
            filtro(x,y) =  1.0 - exp( (-1.0/2.0)*pow(aux,2) );
        }

        return filtro;
    }

    /**
     * retorna un filtro RB (rechaza banda) ideal notch
     * formula:
     *            | 0   si D1(u,v) <= D0  || D2(u,v) <= D0      
     *   H(u,v) = | 
     *            | 1   otro caso
     *
     * D1 = distancia de cada punto al centro positivo del notch (u0,v0)
     * D2 = distancia de cada punto al centro negativo del notch (-u0,-v0)
     * uc = frecuencia de corte
     * vc = frecuencia de corte 
     *      mas que frecuencia de corte es frecuencia (u0,v0) eliminada
     * W  = ancho del filtro (radio del notch, del origen u0,v0) 
     */
    CImg<double> rb_ideal_notch( int width=1, int height=1,
                                 int uc=1, int vc=1, int ancho=1 ) {
        CImg<double> filtro ( width, height, 1, 1, 1 ); // ojo todo 1 
        double distancia_pos = 0.0, distancia_neg = 0.0, aux_pos = 0.0, aux_neg = 0.0;
        int mediox = width/2,
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia_pos = sqrt ( pow(x-mediox-uc,2.0) + pow(y-medioy-vc,2.0) );
            distancia_neg = sqrt ( pow(x-mediox+uc,2.0) + pow(y-medioy+vc,2.0) );
            if ( distancia_pos <= ancho || distancia_neg <= ancho ) {
                filtro(x,y) = 0;
            }
        }

        return filtro;
    }

    CImg<double> rb_butter_notch( int width=1, int height=1,
                                  int uc=1, int vc=1, int ancho=1, int orden=1 ) {
        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia_pos = 0.0, distancia_neg = 0.0, aux = 0.0;
        int mediox = width/2,
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia_pos = sqrt ( pow(x-mediox-uc,2.0) + pow(y-medioy-vc,2.0) );
            distancia_neg = sqrt ( pow(x-mediox+uc,2.0) + pow(y-medioy+vc,2.0) );
            aux = (ancho*ancho) / ( distancia_pos * distancia_neg );
            filtro(x,y) =  1.0 / ( 1.0 + pow( aux, orden) );
        }

        return filtro;
    }

    CImg<double> rb_gaussiano_notch( int width=1, int height=1,
                                     int uc=1, int vc=1, int ancho=1 ) {
        CImg<double> filtro ( width, height, 1, 1, 0 );
        double distancia_pos = 0.0, distancia_neg = 0.0, aux = 0.0;
        int mediox = width/2,
            medioy = height/2;

        cimg_forXY( filtro, x, y) {
            distancia_pos = sqrt ( pow(x-mediox-uc,2.0) + pow(y-medioy-vc,2.0) );
            distancia_neg = sqrt ( pow(x-mediox+uc,2.0) + pow(y-medioy+vc,2.0) );
            aux = ( distancia_pos * distancia_neg ) /  (ancho*ancho);
            filtro(x,y) =  1.0 - exp( (-1.0/2.0) * aux);
        }

        return filtro;
    }

    // ============================================================
    //                     Pasa Banda
    // ============================================================

    /**
     * retorna un filtro AB (pasa banda - acepta banda para no confundir) ideal
     */
    CImg<double> ab_ideal( int width=1, int height=1, int wc=1, int ancho=1 ) {
        CImg<double> Hrb ( rb_ideal( width, height, wc, ancho  ) );
        return ( 1 - Hrb );
    }

    /**
     * retorna un filtro AB (acepta banda) butterworth
     */
    CImg<double> ab_butter( int width=1, int height=1, 
                            int wc=1, int ancho=1, int orden=1 ) {
        CImg<double> Hrb ( rb_butter( width, height, wc, ancho, orden  ) );
        return ( 1 - Hrb );
    }

    /**
     * retorna un filtro AB (pasa banda - acepta banda para no confundir) gaussiano
     */
    CImg<double> ab_gaussiano( int width=1, int height=1, int wc=1, int ancho=1 ) {
        CImg<double> Hrb ( rb_gaussiano( width, height, wc, ancho  ) );
        return ( 1 - Hrb );
    }

    /**
     * retorna un filtro AB (pasa banda - acepta banda para no confundir) ideal notch
     */
    CImg<double> ab_ideal_notch( int width=1, int height=1, 
                                 int uc=1, int vc=1, int ancho=1 ) {
        CImg<double> Hrb ( rb_ideal_notch( width, height, uc, vc, ancho  ) );
        return ( 1 - Hrb );
    }

    /**
     * retorna un filtro AB (pasa banda - acepta banda para no confundir) butter notch
     */
    CImg<double> ab_butter_notch( int width=1, int height=1, 
                                  int uc=1, int vc=1, int ancho=1, int orden=1 ) {
        CImg<double> Hrb ( rb_butter_notch( width, height, uc, vc, ancho, orden  ) );
        return ( 1 - Hrb );
    }

    /**
     * retorna un filtro AB (pasa banda - acepta banda para no confundir) gaussiano notch
     */
    CImg<double> ab_gaussiano_notch( int width=1, int height=1, 
                                  int uc=1, int vc=1, int ancho=1 ) {
        CImg<double> Hrb ( rb_gaussiano_notch( width, height, uc, vc, ancho  ) );
        return ( 1 - Hrb );
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
