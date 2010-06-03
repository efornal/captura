#define UNICODE
#define cimg_use_fftw3
#include <CImg.h>
#include "comun.cpp"
#include <algorithm>

#ifdef cimg_use_fftw3
extern "C" {
#include <fftw3.h>
}
#endif

using namespace cimg_library;
using namespace std;

/**
 *
 *
 * ESTE EJERCICIO NO HACE LO QUE PIDE EL ENUNCIADO!!!
 * sólo pruebo los filtros que defini en comun.cpp y chau
 *
 *
 */
int main(int argc, char *argv[]) {

  const char *i1 = cimg_option( "-img1", "../img/morrissey.jpg", "imagen 1" );
  const char *i2 = cimg_option( "-img2", "../img/huang1.jpg", "imagen 2" );

  CImg<double> imag1( i1 ), imag2( i2 );

  filtro_pb_ideal<double>(256,256,30).display("pb ideal, wc=30");
  filtro_pa_ideal<double>(256,256,30).display("pa ideal, wc=30");
  filtro_pb_gauss<double>(256,256,30).display("pb gauss, var=30");
  filtro_pa_gauss<double>(256,256,30).display("pa gauss, var=30");
  CImg<double> covar(2,2,1,1,0);
  covar(0,0)=20.0;  covar(0,1)=1.0;  covar(1,1)=20.0;  covar(1,0)=1.0;
  filtro_pb_gauss<double>(256,256,covar).display("pb gauss, matriz cov");
  filtro_pa_gauss<double>(256,256,covar).display("pa gauss, matriz de covar");
  filtro_pb_butter<double>(256,256,30,2).display("pb butter, wc=30, orden 2");
  filtro_pa_butter<double>(256,256,30,20).display("pa butter, wc=30, orden 20");

  return 0;
}
