/**
 * POSTA: a todos los filtrados (al menos en segmentacion)
 * le aplicamos abs(), es la forma correcta de verlos.
*/

#define pdi_segmentacion 1
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#include <masks.h>

using namespace std;
using namespace cimg_library;


CImg<double> filtrado_roberts( CImg<double> img ) {
    return 
        img.get_convolve( masks::roberts_gx() ).abs() +
        img.get_convolve( masks::roberts_gy() ).abs();
}

CImg<double> filtrado_prewitt( CImg<double> img ) {
    return 
        img.get_convolve( masks::prewitt_gx() ).abs() +
        img.get_convolve( masks::prewitt_gy() ).abs() +
        img.get_convolve( masks::prewitt_gxy() ).abs() +
        img.get_convolve( masks::prewitt_gyx() ).abs();
}

CImg<double> filtrado_sobel( CImg<double> img ) {
    return 
        img.get_convolve( masks::sobel_gx() ).abs() +
        img.get_convolve( masks::sobel_gy() ).abs() +
        img.get_convolve( masks::sobel_gxy() ).abs() +
        img.get_convolve( masks::sobel_gyx() ).abs();
}

CImg<double> filtrado_laplaciano_g( CImg<double> img ) {
    return img.get_convolve( masks::laplaciano_g() ).abs();
}


/**
 * Transformada Hough directa
 *
 * Todavia no funciona el cuantizado del plano ro-theta
 * tomada de funciones de la catedra
 *
 *                        alto                  alto
 * escala rho = ---------------------------  = ------
 *              2 * sqrt{ alto^2 + ancho^2 }   2sqrt{D}
 *
 * NOTA: D = sqrt{ alto^2 + ancho^2 }, se multiplica por 2
 * para armar el acumulador con parte positiva y negativa
 * 
 * escala theta = ancho / pi

 * M_PI = valor de pi, puede definirse si no esta como:
 * ifndef...define M_PI           3.14159265358979323846
 *
 */            
template<class T>
CImg<T> hough_directa( CImg<T> img ) {

  CImg<double> hough(img); 
  const unsigned width  = img.width();
  const unsigned height = img.height();

  hough.fill(0.0);
  double d_rho   = height / (2 * sqrt( pow(float(height),2) + pow(float(width),2) )),
      d_theta = width/M_PI, // ancho/pi
      rho, theta;

  for ( unsigned y = 0; y < height; y++ ) {
      for ( unsigned x = 0; x < width; x++ ) {
          if ( img(x,y) > 0.5 ) {
              for ( unsigned t = 0; t < width; t++ ) {
                  theta = t/d_theta - M_PI/2;
                  rho   = x*cos(theta) + y*sin(theta);
                  unsigned r  = (unsigned)( rho*d_rho + height/2.0 );
                  hough(t,r) += 1;
              }
          }
      }
  }
  return hough;
}
/**

*/
template<class T>
CImg<T> filtrar_hough( CImg<T> hough, 
                       double u_rho, 
                       double u_theta,
                       double tol_rho = 0.1,
                       double tol_theta = 0.1 ) {
    int width  = hough.width();
    int height = hough.height();
    double d_rho = height / (2.0 * sqrt( pow(float(height),2) + pow(float(width),2) )),
        d_theta = width/M_PI, // ancho/pi
        theta, rho;
    for ( unsigned y = 0; y < height; y++ ) {
        for ( unsigned x = 0; x < width; x++ ) {
            if ( hough(x,y) > 0.5 ) {
                for ( unsigned t = 0; t < width; t++ ) {
                    theta = t/d_theta - M_PI/2;
                    rho   = x*cos(theta) + y*sin(theta);
                    hough(x,y) = (
                                  ( theta < u_theta+tol_theta && 
                                    theta > u_theta-tol_theta ) &&
                                  ( rho < u_rho+tol_rho && 
                                    rho > u_rho-tol_rho )
                                  ) ? 0 : 1;
                        //printf("p si %f < %f && %f > %f \n",
                        //     rho,u_rho+tol_rho, rho,u_rho-tol_rho    );


                }
            }
        }
    }
    printf("o = %f  p = %f    o = %f  p = %f \n", theta,rho,theta+tol_theta,rho+tol_rho);
    return hough;
}
/**

*/
template<class T>
CImg<T> filtrar_hough_rho( CImg<T> hough, 
                       double u_rho, 
                       double tol_rho = 0.1 ) {
    int width  = hough.width();
    int height = hough.height();
    double d_rho = height / (2.0 * sqrt( pow(float(height),2) + pow(float(width),2) )),
        d_theta = width/M_PI, // ancho/pi
        theta, rho;
    for ( unsigned y = 0; y < height; y++ ) {
        for ( unsigned x = 0; x < width; x++ ) {
            if ( hough(x,y) > 0.5 ) {
                for ( unsigned t = 0; t < width; t++ ) {
                    theta = t/d_theta - M_PI/2;
                    rho   = x*cos(theta) + y*sin(theta);
                    hough(x,y) = ( rho < u_rho+tol_rho && 
                                   rho > u_rho-tol_rho ) ? 1 : 0;
                        //printf("p si %f < %f && %f > %f \n",
                        //     rho,u_rho+tol_rho, rho,u_rho-tol_rho    );
                }
            }
        }
    }
    return hough;
}
/**

*/
template<class T>
CImg<T> filtrar_hough_theta( CImg<T> hough, 
                       double u_theta, 
                       double tol_theta) {
    int width  = hough.width();
    int height = hough.height();
    double d_rho = height / (2.0 * sqrt( pow(float(height),2) + pow(float(width),2) )),
        d_theta = width/M_PI, // ancho/pi
        theta, rho;

    for ( unsigned y = 0; y < height; y++ ) {
        for ( unsigned x = 0; x < width; x++ ) {
            if ( hough(x,y) > 0.5 ) {
                for ( unsigned t = 0; t < width; t++ ) {
                    theta = t/d_theta - M_PI/2;
                    rho   = x*cos(theta) + y*sin(theta);
                    unsigned r  = (unsigned)( rho*d_rho + height/2.0 );
                    if ( sqrt(theta*theta-u_theta*u_theta) <= tol_theta ) {
                        hough(t,r) = 1;
                        printf("if %f <= %f   => %f \n",
                               abs((theta-u_theta)),
                               tol_theta,
                               hough(t,r) );

                    } else {
                        hough(t,r) = 0;
                        /* printf("if %f <= %f   => %f \n", */
                        /*        abs((theta-u_theta)), */
                        /*        tol_theta, */
                        /*        hough(t,r) ); */

                    }
                }
            }
        }
    }
    return hough;
}

/**
 * Transformada Hough inversa
 *
 * tomada de funciones de la catedra
 */
template <class T>
CImg<T> hough_inversa( CImg<T> img ) {

  const double color[] = {255.f, 0.0f, 0.0f};
  CImg<double> hough(img); 
  hough.fill(0.0);
  int width  = img.width(), 
      height = img.height(),
      y0, y1;

  double scale_rho   = height / (2 * sqrt( pow(float(height),2) + pow(float(width),2) ) ),
         scale_theta = width / M_PI,
         rho, theta;

  for ( unsigned b = 0; b < height; b++ ){
      for ( unsigned a=0; a < width; a++ ) {
          if ( img(a,b) > 0.5 ) {
              theta = a/scale_theta - M_PI/2;
              y0 = (int)(((b-(height/2.0))/scale_rho) / sin(theta)); // -0/tan(theta));
              y1 = (int)(((b-(height/2.0))/scale_rho) / sin(theta) - width/tan(theta));
              hough.draw_line( 0, (int)y0, (int)width, (int)y1, color );
          }
      }
  }
  return hough;
}




/**
 * solo maximos de la t hough
 */
template <class T>
CImg<T> get_solo_maximos( CImg<T> img, int cantidad=1 ) {

    CImg<T> maximos(cantidad,1,1,1,0);
    CImg<T> aux(img);
    int cont = 0;
    for ( int i = 0; i < cantidad; i++ ) {
        maximos(cont++) = img.max();
        img.max() = 1;
    }
    cimg_forXY(img,x,y){
        if ( img(x,y) == aux(x,y) ) img(x,y) = 0;
    }
    return img;
}

/**
 * segmenta una imagen segun la semilla inicial x,y, 
 * con una cierta tolerancia y usa 4 vecinos para la comparacion
 *
 * @param: x_inicial: posicion en x del pixel a segmentar
 * @param: y_inicial: posicion en y del pixel a segmentar
 * @param: intensidad: intensidad del pixel a segmentar
 * @param: widht: ancho de la imagen pasada como parametro
 * @param: height: alto de la imagen pasada como parametro
 * @param: tolerancia: tolerancia con la que se segmenta intendidad+- tolerancia.
 * @param: imagen: imagen sobre la cual se aplica la segmentacion
 * @param: imagen_segmentada: imagen segmentada que es devuelta por referencia. 
 *         (incialmente debe ser una del mismo tamanio que  imagen y rellenada con negro.
 * @param: cant_vecinos(valores aceptados=4 o 8): es la cantidad de vecinos 
 *         que se usan para comparar. 4 por defecto
 * */

template<class T>
void explorar_intensidad( int x_inicial, 
                          int y_inicial, 
                          T intensidad, 
                          int width,
                          int height, 
                          float tolerancia, 
                          CImg<T> &imagen,
                          CImg<T> &imagen_segmentada, 
                          int cant_vecinos = 4) {

    if ( x_inicial > width  - 1 || x_inicial < 0 || 
         y_inicial > height - 1 || y_inicial < 0) {
        return;
    }

    int valor = intensidad - tolerancia;
    if (valor < 0) valor = 0;

    if ( (imagen( x_inicial, y_inicial) <= (intensidad + tolerancia) && 
          imagen( x_inicial, y_inicial) >= valor ) && 
         imagen_segmentada( x_inicial, y_inicial ) == 0) {

        imagen_segmentada( x_inicial, y_inicial ) = 1;

        if ( cant_vecinos == 8 ) { // la diagonal y luego el resto
            //esquina superior izquierda
            explorar_intensidad( x_inicial - 1, y_inicial - 1, intensidad,
                                 width, height, tolerancia, 
                                 imagen, imagen_segmentada);
            //esquina superior derecha 
            explorar_intensidad( x_inicial - 1, y_inicial + 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
            //esquina inferior izquierda
            explorar_intensidad( x_inicial + 1, y_inicial - 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
            //esquina inferior derecha
            explorar_intensidad( x_inicial + 1, y_inicial + 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
        } // si no selecciono los 8 solo hago los 4 vecinos:

        //vecino inferior centro
        explorar_intensidad( x_inicial + 1, y_inicial, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino vecindo derecho centro
        explorar_intensidad( x_inicial, y_inicial + 1, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino superior centro
        explorar_intensidad( x_inicial - 1, y_inicial, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino izquierdo centro
        explorar_intensidad(x_inicial, y_inicial - 1, intensidad, width,
                            height, tolerancia, imagen, imagen_segmentada);
    } else {
        return;
    }
}

/** 
 * Funcion wrapper que segmenta una imagen en base al parecido con sus vecinos
 * intensidad del vecino+-tolerancia
 * devuelve una imagen binaria pintada de blanco la parte segmentada.
 * SOLO SIRVE PARA IMAGENES DE 1 solo canal!
 * @param: imagen_a_segmentar: es la imagen sobre la cual se quiere realizar 
 *         la segmentacion
 * @param: x_inicial: posicion en x del pixel a segmentar
 * @param: y_inicial: posicion en y del pixel a segmentar
 * @param: tolerancia: los pixeles segemntados seran aquellos que cumpla con 
 *         intensidad+-tolerancia..
 * @param: cantidad_vecinos(Val. posibles: 4 u 8): cantidad de vecinos usados 
 *         en la segmentacion 4->cruz, 8->_todo el borde
 */
template<class T>
CImg<T> segmentar_binario( CImg<T> imagen_a_segmentar, 
                   int x_inicial, 
                   int y_inicial,
                   float tolerancia = 50.0, 
                   int cantidad_vecinos = 4) {

    int width = imagen_a_segmentar.width();
    int height = imagen_a_segmentar.height();
    T intensidad = imagen_a_segmentar(x_inicial, y_inicial);

    CImg<T> imagen_segmentada ( imagen_a_segmentar.width(),
                                imagen_a_segmentar.height(), 1, 1, 0); //relleno con ceros

    // criterio de segmentacion, modificar para cambiar criterio
    explorar_intensidad ( x_inicial, y_inicial, intensidad, 
                          width, height, tolerancia, 
                          imagen_a_segmentar, imagen_segmentada, cantidad_vecinos );

    return imagen_segmentada;
}

/** 
 * forma la imagen segmentada tomando los tonos de grises de la img original
 * a partir de los valores en la mascara binaria ya segmentada
 *
 * Lo que este blanco en imagen_binaria es remplazado por lo que tenga 
 * la imagen_original y es devuelto en una nueva imagen
 */
template<class T>
CImg<T> binaria_a_grises ( CImg<T> imagen_binaria, CImg<T> imagen_original ) {

    // imagen original rellena con cero de entrada
    CImg<T> imagen ( imagen_original.width(), imagen_original.height(), 1, 1, 0); 

    cimg_forXY( imagen_binaria, x, y ) {
        if ( imagen_binaria(x, y) != 0 ) {
            imagen(x,y) = imagen_original(x,y);
        }
    }
    return imagen;
}
