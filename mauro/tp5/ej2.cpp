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

int main(int argc, char *argv[]) {

  const char *i1 = cimg_option( "-img1", "../img/morrissey.jpg", "imagen 1" );
  const char *i2 = cimg_option( "-img2", "../img/huang1.jpg", "imagen 2" );

  CImg<double> imag1( i1 ), imag2( i2 );

  int w = min( imag1.width(), imag2.width() ),
    h = min( imag1.height(), imag2.height() );

  imag1.channel(0).normalize(0,255).resize(w,h);
  imag2.channel(0).normalize(0,255).resize(w,h);

  CImgList<double> fft1 = imag1.get_FFT();
  CImgList<double> fft2 = imag2.get_FFT();

  fft1 = realimag2magfase ( fft1 );
  fft2 = realimag2magfase ( fft2 );
  
  CImgList<double> solo_fase(fft1), solo_mag(fft1);
  
  solo_fase[0].fill(1);
  solo_mag[1].fill(0);

  solo_fase=magfase2realimag( solo_fase );
  solo_mag =magfase2realimag( solo_mag );

  solo_fase.FFT(true);
  solo_mag.FFT(true);

  CImgList<double>(solo_fase[0].get_normalize(0,255),
		   solo_mag[0].get_normalize(0,255) ).display( "Solo fase/Solo mag" );

  CImgList<double> combi1( fft1[0], fft2[1] ), combi2( fft2[0], fft1[1] );

  combi1=magfase2realimag( combi1 );
  combi2=magfase2realimag( combi2 );

  combi1.FFT(true);
  combi2.FFT(true);

  CImgList<double>(combi1[0].get_normalize(0,255),
		   combi2[0].get_normalize(0,255) ).display( "Combinacion 1/Combinacion 2" );

  return 0;
}
