#include <CImg.h>
#include <math.h>

using namespace cimg_library;

namespace masks {

    /**
       retorna una mascara impulso:
       *  0 0 0
       *  0 1 0
       *  0 0 0
     */
    CImg<float> impulso( ) {
        int x=3, y=3, z=1, c=1;
        CImg<float> mask( x, y, z, c, 0 );
        mask(1,1) = 1;
        return mask;
    }

    // =============== filtros de suavizado ============
    // pesos positivos que suman 1

    // =============== filtros promediadores ============
    // pesos iguales

    /**
       retorna una mascara promediadora tipo media estandar
       *  1 1 1
       *  1 1 1 * 1/9
       *  1 1 1
     */
    CImg<double> media_estandar( double k=(1/9.0) ) {
        int x=3, y=3, z=1, c=1;
        CImg<double> mask( x, y, z, c, 1);
        mask *= k;
        return mask;
    }

    /**
       retorna una mascara promediadora en forma de signo mas
       *  0 1 0
       *  1 1 1 * 1/5
       *  0 1 0
     */
    CImg<double> signo_mas( double k=(1/5.0) ) {
        int x=3, y=3, z=1, c=1;
        CImg<double> mask( x, y, z, c, 1);
        mask *= k;
        return mask;
    }

    /**
       retorna una mascara promediado ponderado
       *  1 2 1
       *  2 4 2 * 1/16
       *  1 2 1
     */
    CImg<float> media_ponderada( float k=(1/16.0) ) {
        int x=3, y=3, z=1, c=1;
        CImg<float> mask( x, y, z, c, 1 );
        mask(1,0) *= 2;
        mask(0,1) *= 2;
        mask(1,2) *= 2;
        mask(2,1) *= 2;
        mask(1,1) *= 4;
        mask *= k;
        return mask;
    }

    /**
     * retorna una mascara promediadora de tamanio especificado 
     * por defecto k = 1/N^2   (N = m*n)
     * m * 1/N^2  N = m*n
     *
     *  1 1 . 1
     *  1 1 . 1 * 1/N^2   (N = m*n)
     *  . . . 1
     *  1 1 1 1
     */
    CImg<double> promedio( int x=3, int y=3, double k=0 ) {
        int z=1, c=1;
        k = ( k == 0 ) ? ( 1.0/(x*y) ) : k; // N^2 por defecto
        CImg<double> mask( x, y, z, c, 1);
        return  ( mask * k );
    }

    // =============== filtros no simetrico ============
    // no simetrico si A != A transpuesta
    
    /**
       retorna una mascara no simetrica
       *  1 3 1                      1 2 1
       *  2 1 2 * 1/15  transpuesta= 3 1 3 => no simetrica
       *  1 3 1                      1 2 1
     */
    CImg<double> asimetrica() {
        int x=3, y=3, z=1, c=1;
        CImg<double> mask( x, y, z, c, 1);
        mask(1,0) = 3; 
        mask(1,2) = 3; 
        mask(0,1) = 2; 
        mask(2,1) = 3; 
        return mask;
    }

    // =============== filtros pasa bajos: gausseana ============
    
    /**
       retorna una mascara gausseana
       *  formula: 1/sqrt(2pi) * e^-(x^2 + y^2)/2var^2
       * dada la formula, con +-x = x^2 , e y+- = y^2
       * por lo que siempre retorna una mascara tipo signo mas
       *  0  a  0
       *  a 255 a 
       *  0  a  0
       * FIXME : no funciona para valores diferentes de 3x3 !
       *  
     */
     CImg<double> gaussiana( int x=3, int y=3, double var=1 ) {
         CImg<double> mask( x, y, 1, 1, 1); 
         double pi = 4.0*atan(1.0); 
         double c = 1.0/sqrt(2.0*pi);
         double den = 2.0 * pow(var,2);
         cimg_forXY(mask, x, y){
             mask(x,y) =  exp( -(pow(x-1,2) + pow(y-1,2)) / den );
         }
        return ( mask *= c );
    }

}
