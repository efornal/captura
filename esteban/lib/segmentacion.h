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
CImg<T> hough_directa( CImg<T> img, 
                       double dtheta = 1, 
                       double drho = 1, 
                       bool getHist = 0 ) {

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
