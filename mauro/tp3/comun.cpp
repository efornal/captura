#define UNICODE
#include <CImg.h>
#include <algorithm>

using namespace cimg_library;
using namespace std;

/**
 * genera un kernel gaussiano de wxh, con varianza var y media mean
 */
template<class T>
CImg<T> kernel_gaussiano( unsigned w, unsigned h, double var=0.4, double mean=0.5 ) {
  CImg<T> k ( w, h, 1, 1 );
  unsigned x,y;
  cimg_forXY ( k, x, y ) {
    k(x,y) = exp( -( pow(x-(w-1)*mean,2)+pow(y-(h-1)*mean,2) ) / pow(var*w,2) );
  }
  return k;
}

/**
 * genera un kernel de promediado (uniforme), con suma suma
 */
template<class T>
CImg<T> kernel_promedio( unsigned w, unsigned h, double suma=1.0 ) {
  CImg<T> k ( w, h, 1, 1, (T)(suma/w*h) );
  // unsigned x,y;
  // cimg_forXY ( k, x, y ) {
  //   k(x,y) = exp( -( pow(x-(w-1)*mean,2)+pow(y-(h-1)*mean,2) ) / pow(var*w,2) );
  // }
  return k;
}

//distancia euclidea
template<class T>
double dist_2( T x0, T y0, T x1, T y1 ) {
  return sqrt( pow(x1-x0,2)+pow(y1-y0,2) );
}


//distancia euclidea al cuadrado
template<class T,class U>
double dist_2ala2( T x0, T y0, U x1, U y1 ) {
  return pow(x1-x0,2)+pow(y1-y0,2);
}

#define __PI__ 3.1415279

// HORRIBLE!!!!!!!!!!! CORREGIR!!!!!!!!!!!!!!!!!!!!!!
template<class T>
CImg<T> kernel_mexican_hat( unsigned w, unsigned h, double sigma=1.0 ) {
  CImg<T> k ( w, h, 1, 1 );

  // Sombrero Mejicano:
  // \psi(t)={2\over{\sqrt{3\sigma}\pi^{1\over 4}}}\left(1-{t^2\over\sigma^2}\right)e^{-t^2\over 2\sigma^2}
  // pero uso esta versión simplificada:
  // \psi(x,y)= -2\pi\left(x^2+y^2\right)e^{-\frac{1}{2}\left(x^2+y^2\right)}

  unsigned x,y;
  cimg_forXY ( k, x, y ) {
    k(x,y) = (1-( dist_2ala2(x,y,(w-1)/2,(h-1)/2)/pow(sigma,2))) * 
      exp( -(dist_2ala2(x,y,(w-1)/2,(h-1)/2))/(2*pow(sigma,2)) );
  }
  
  return k;
}
