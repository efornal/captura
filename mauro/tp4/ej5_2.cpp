#define UNICODE
#include <CImg.h>
//#include <vector>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
//using namespace std;



int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "../img/camino.tif", "imagen" );

  CImg<double> mask = LoG_mask(5,0.9);
  // mask(0,1) = -1;  mask(1,0) = -1;  mask(2,1) = -1;  mask(1,2) = -1;
  // mask(0,0) = -1;  mask(2,0) = -1;  mask(0,2) = -1;  mask(2,2) = -1;
  // mask(1,1) = 9;

  CImg<double> rgb( im ), r=rgb.get_channel(0), g=rgb.get_channel(1), b=rgb.get_channel(2);
  CImg<double> eq_comp( rgb );

  r.convolve(mask);
  g.convolve(mask);
  b.convolve(mask);

  unsigned x, y;
  cimg_forXY( eq_comp, x, y ) {
    eq_comp(x,y,0,0) = r(x,y);
    eq_comp(x,y,0,1) = g(x,y);
    eq_comp(x,y,0,2) = b(x,y);
  }

  //  eq_comp.normalize(0,255);

  CImg<double> eq_int(rgb);

  eq_int.RGBtoHSI();

  CImg<double> i=eq_int.get_channel(2);

  i.convolve(mask);

  cimg_forXY( eq_int, x, y ) {
    eq_int(x,y,0,2) = i(x,y);
  }

  eq_int.HSItoRGB();

  //  eq_int.normalize(0,255);

  CImg<double>orig( im );
  // orig.normalize(0,255);

  CImgList<double>( eq_comp, eq_int, orig ).display("Conv. por componentes RGB / conv. solo intensidad / original");

  return 0;
}
