#define UNICODE
#include <CImg.h>
//#include <vector>
#include "comun.cpp"
//#include "CPDSI_functions.h"

using namespace cimg_library;
//using namespace std;

int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "../img/chairs_oscura.tif", "imagen" );
  const char *ch = cimg_option( "-img", "../img/chairs.tif", "imagen" );

  CImg<double> rgb( im ), r=rgb.get_channel(0), g=rgb.get_channel(1), b=rgb.get_channel(2);
  CImg<double> eq_comp( rgb );

  r.equalize(256);
  g.equalize(256);
  b.equalize(256);

  unsigned x, y;
  cimg_forXY( eq_comp, x, y ) {
    eq_comp(x,y,0,0) = r(x,y);
    eq_comp(x,y,0,1) = g(x,y);
    eq_comp(x,y,0,2) = b(x,y);
  }

  //  eq_comp.display();

  CImg<double> eq_int(rgb);

  eq_int.RGBtoHSI();

  CImg<double> i=eq_int.get_channel(2);

  i.equalize(256);

  cimg_forXY( eq_int, x, y ) {
    eq_int(x,y,0,2) = i(x,y);
  }

  eq_int.HSItoRGB();

  //eq_int.display();

  CImg<double>orig( ch );

  CImgList<double>( eq_comp, eq_int, orig ).display("Eq por componentes RGB / eq. intensidad / original");

  return 0;
}
