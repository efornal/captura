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
  double gl = cimg_option( "-gl", 0.4, "ganancia luminancia" );
  double gh = cimg_option( "-gh", 1.3, "ganancia reflectancia" );
  double D0 = cimg_option( "-D0", 40.0, "D0" );
  double c = cimg_option( "-c", 2.0, "control pendiente entre gl - gh" );
  CImg<double> imag( i1 );

  filtro_homo ( imag.width(), imag.height(), gl, gh, D0, c, true ).display("filtro homo");

  CImgList<double>( imag.get_channel(0).normalize(0,1),
		    filtrar_homo<double>(imag,gl,gh,D0,c).normalize(0,1)
		    ).display("imagen original / imagen filtrada");

  return 0;
}
