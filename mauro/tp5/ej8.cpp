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

  const char *i1 = cimg_option( "-img1", "../img/camaleon.tif", "imagen 1" );
  double a = cimg_option( "-a", 1.0, "parametro a de filtro EAF" );
  double b = cimg_option( "-b", 5.0, "parametro b de filtro EAF" );
  double A = cimg_option( "-A", 4.0, "parametro A de filtro AP" );

  CImg<double> imag( i1 );

  CImg<double> filtro = filtro_eaf( filtro_pa_butter<double>( imag.width(), imag.height(), 30.0, 6.0), a, b);

  CImgList<double>( imag.normalize(0,1),
		    filtrar<double>(imag,filtro).normalize(0,1)
		    ).display("imagen original / imagen filtrada");

  return 0;
}

