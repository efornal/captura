#ifndef pdi_masks
#define pdi_masks 1

#include <CImg.h>
#include <math.h>

using namespace cimg_library;

namespace masks {

    /**
     * retorna una mascara impulso:
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

    // =============== filtros PB: promediadores ============
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

    // =============== filtros PB: gausseana ============
    
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

    /**
     * retorna una mascara gausseana (de la lib de catedra)
     * formula:
     *   mask = 1 / (2*pi*s^2) * exp(-(x^2+y^2)/(2*s^2))     s=sigma
     */
    CImg<double> gaussian(int size, double sigma) {
        int ini,fin;
        double pi=3.14159;
        double aux;
        CImg<double> mask(size,size);
        int x,y;
        ini=(int)(-1)*(size-1)/2;
        fin=(int)(size-1)/2;
        for (x=ini;x<fin+1;x++){
            for (y=ini;y<fin+1;y++){
                aux=((double)(x*x)+(double)y*y)/(2*sigma*sigma);
                mask(x-ini,y-ini)=1/(2*pi*sigma*sigma)*exp(-1*aux);
            }
        }
        CImg<> stats=mask.get_stats();
        for (x=0;x<size;x++){
            for (y=0;y<size;y++){
                if (mask(x,y)<10e-5*stats(0,2)){
                    mask(x,y)=0;
                }
            }
        }
        mask/=mask.sum();
        return mask;
    }

    // =============== filtros PA: acentuados ============

    /**
     * retorna una mascara gausseana (de la lib de catedra)
     * con forma de pasa altos
     *  formula: 1/sqrt(2pi) * e^-(x^2 + y^2)/2var^2
     * dada la formula, con +-x = x^2 , e y+- = y^2
     */
    CImg<double> pa_gaussian(int size, double sigma) {
        int ini,fin;
        double pi=3.14159;
        double aux;
        CImg<double> mask(size,size);
        int x,y;
        ini=(int)(-1)*(size-1)/2;
        fin=(int)(size-1)/2;
        for (x=ini;x<fin+1;x++){
            for (y=ini;y<fin+1;y++){
                aux=((double)(x*x)+(double)y*y)/(2*sigma*sigma);
                mask(x-ini,y-ini)= 1 - 1/(2*pi*sigma*sigma)*exp(-1*aux);
            }
        }
        CImg<> stats=mask.get_stats();
        for (x=0;x<size;x++){
            for (y=0;y<size;y++){
                if (mask(x,y)<10e-5*stats(0,2)){
                    mask(x,y)=0;
                }
            }
        }
        mask/=mask.sum();
        return mask;
    }
    
    /**
       retorna filtro pasa altos con suma 1
       * la suma de todos los coef da 1,
       *  0  -1   0
       * -1   5  -1 
       *  0  -1   0
       *  
     */
     CImg<double> suma_uno_bajo( ) {
         CImg<double> mask( 3, 3, 1, 1, 0);
         mask(1,0) = -1;
         mask(0,1) = -1;
         mask(2,1) = -1;
         mask(1,2) = -1;
         mask(1,1) =  5;
         return mask;
     }

    /**
       retorna filtro pasa altos con suma 1
       * la suma de todos los coef da 1,
       * -1  -1  -1
       * -1   9  -1 
       * -1  -1  -1
       *  
     */
     CImg<double> suma_uno_alto( ) {
         CImg<double> mask( 3, 3, 1, 1, -1);
         mask(1,1) =  9;
         return mask;
     }

    /**
       retorna filtro pasa altos con suma 1
       * la suma de todos los coef da 1,
       *  1  -2   1
       * -2   5  -2 
       *  1  -2   1
       *  
     */
     CImg<double> suma_uno_medio( ) {
         CImg<double> mask( 3, 3, 1, 1, 1);
         mask(1,1) =  5;
         mask(0,1) =  -2;
         mask(1,0) =  -2;
         mask(2,1) =  -2;
         mask(1,2) =  -2;
         return mask;
     }

    /**
       retorna filtro pasa altos con suma 0
       * la suma de todos los coef da 0,
       * -1  -1  -1
       * -1   8  -1 
       * -1  -1  -1
       *  FIXME: no deberia multiplicar luego por 1/9 para normalizar?
     */
     CImg<double> suma_cero( ) {
         CImg<double> mask( 3, 3, 1, 1, -1);
         mask(1,1) =  8;
         return mask;
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

    //==================================================
    //                 SEGMENTACION
    //==================================================
    /**
     * mascara generica:
     *                  | z1  z2  z3 |
     *                  | z4  z5  z6 |
     *                  | z7  z8  z9 |
     */

    /**
     * retorna una mascara de Roberts Gx
     *  Gx = z9 - z5
     *   -1  0   
     *    0  1   
     */
    CImg<double> roberts_gx() {
        CImg<double> mask( 2, 2, 1, 1, 0);
        mask(0,0) = -1;
        mask(1,1) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Roberts Gy
     *  Gx = z8 - z6
     *   0  -1   
     *   1   0    
     */
    CImg<double> roberts_gy() {
        CImg<double> mask( 2, 2, 1, 1, 0);
        mask(1,0) = -1;
        mask(0,1) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Prewitt Horizontal
     *  Gx = (z7 + z8 + z9) - (z1 + z2 + z3)
     *   -1  -1  -1   
     *    0   0   0   bordes ---
     *    1   1   1
     */
    CImg<double> prewitt_gx() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        cimg_forX(mask,x){
            mask(x,0) = -1;
            mask(x,2) =  1;
        }
        return mask;
    }

    /**
     * retorna una mascara de Prewitt Vertical
     *  Gx = (z3 + z6 + z9) - (z1 + z4 + z7)
     *   -1   0   1   
     *   -1   0   1   bordes |
     *   -1   0   1
     */
    CImg<double> prewitt_gy() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        cimg_forY(mask,y){
            mask(0,y) = -1;
            mask(2,y) =  1;
        }
        return mask;
    }

    /**
     * retorna una mascara de Prewitt Diagonal x->y
     *   0   1   1   
     *  -1   0   1   bordes                     \
     *  -1  -1   0
     */
    CImg<double> prewitt_gxy() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,1) = -1;
        mask(0,2) = -1;
        mask(1,2) = -1;
        mask(1,0) =  1;
        mask(2,0) =  1;
        mask(2,1) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Prewitt Diagonal y->x
     *   -1  -1   0   
     *   -1   0   1   bordes /
     *    0   1   1
     */
    CImg<double> prewitt_gyx() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,0) = -1;
        mask(0,1) = -1;
        mask(1,0) = -1;
        mask(2,1) =  1;
        mask(2,2) =  1;
        mask(1,2) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Sobel Horizontal
     * Gx = (z7 + 2z8 + z9) - (z1 + 2z2 + z3)
     *  -1  -2  -1
     *   0   0   0   bordes --
     *   1   2   1
     */
    CImg<double> sobel_gx() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,0) = -1;
        mask(1,0) = -2;
        mask(2,0) = -1;
        mask(0,2) =  1;
        mask(1,2) =  2;
        mask(2,2) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Sobel Vertical
     * Gy = (z3 + 2z6 + z9) - (z1 + 2z4 + z7)
     *  -1   0   1
     *  -2   0   2   bordes |
     *  -1   0   1
     */
    CImg<double> sobel_gy() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,0) = -1;
        mask(0,1) = -2;
        mask(0,2) = -1;
        mask(2,0) =  1;
        mask(2,1) =  2;
        mask(2,2) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Sobel Diagonal x->y
     *   0   1   2
     *  -1   0   1   bordes \
     *  -2  -1   0
     */
    CImg<double> sobel_gxy() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,1) = -1;
        mask(0,2) = -2;
        mask(1,2) = -1;
        mask(1,0) =  1;
        mask(2,0) =  2;
        mask(2,1) =  1;
        return mask;
    }

    /**
     * retorna una mascara de Sobel Diagonal y->x
     *  -2  -1   0
     *  -1   0   1   bordes /
     *   0   1   2
     */
    CImg<double> sobel_gyx() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,0) = -2;
        mask(0,1) = -1;
        mask(1,0) = -1;
        mask(2,1) =  1;
        mask(2,2) =  2;
        mask(1,2) =  1;
        return mask;
    }

    /**
     * retorna una mascara Laplaciano N4
     * Lap{f} = gradiente{f}^2 = 4z5 - (z2 + z4 + z6 + z8)
     *   0  -1   0
     *  -1   4  -1    N=4
     *   0  -1   0
     */
    CImg<double> laplaciano_n4() {
        CImg<double> mask( 3, 3, 1, 1, 0);
        mask(0,1) = -1;
        mask(1,0) = -1;
        mask(1,2) = -1;
        mask(2,1) = -1;
        mask(1,1) =  4;
        return mask;
    }

    /**
     * retorna una mascara Laplaciano N8
     * Lap{f} = gradiente{f}^2 = 8z5 - (z1 + z2 + + z3 + z4 + z6 + z7 + z8)
     *  -1  -1  -1
     *  -1   8  -1    N=8
     *  -1  -1  -1
     */
    CImg<double> laplaciano_n8() {
        CImg<double> mask( 3, 3, 1, 1, -1);
        mask(1,1) =  8;
        return mask;
    }

    /**
     * retorna una mascara Laplaciano del gaussiano - LoG
     *
     *              - r^2 / 2sigma^2
     *  h(r)   = -e
     *
     *              (r^2) - sigma^2     - r^2 / 2sigma^2
     *  Lap{h} = -  --------------- . e
     *                  sigma^4     
     *
     *    con  r^2 = (x^2 + y^2)
     *
     *   0   0   -1   0   0
     *   0  -1   -2  -1   0
     *  -1  -2   16  -2  -1
     *   0  -1   -2  -1   0
     *   0   0   -1   0   0
     */
    CImg<double> laplaciano_g() {
        CImg<double> mask( 5, 5, 1, 1, 0);
        mask(0,2) =  -1;
        mask(1,1) =  -1;
        mask(1,3) =  -1;
        mask(2,0) =  -1;
        mask(2,4) =  -1;
        mask(3,1) =  -1;
        mask(3,3) =  -1;
        mask(4,2) =  -1;
        mask(1,2) =  -2;
        mask(2,1) =  -2;
        mask(2,3) =  -2;
        mask(3,2) =  -2;
        mask(2,2) =  16;
        return mask;
    }

}
#endif
