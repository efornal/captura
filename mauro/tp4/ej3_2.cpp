#define UNICODE
#include <CImg.h>
#include <vector>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
using namespace std;


int main(int argc, char *argv[]) {

  const char *im = cimg_option( "-img", "", "imagen" );
  const char *pa = cimg_option( "-pal", "", "paleta" );

  if ( strlen( pa ) == 0 ) {
    printf( "error: no se puede no especificar una paleta\n" );
    return 1;
  }

  vector<vector<float> > v_paleta;
  cargar_paleta( v_paleta, pa );

  CImg<unsigned char> index;
  CImg<double> indexada;
  unsigned char x,y;

  if ( strlen( im ) == 0 ) {
    index.assign(256,256,1,1);
    cimg_forXY(index,x,y) {
      index(x,y) = x;
    }
    indexada.assign(256,256,1,3);
  } else {
    index.assign( im );
    indexada.assign( index.width(), index.height(), 1, 3 );
  }

  cimg_forXY(index, x, y) {
    indexada(x,y,0,0) = v_paleta[index(x,y)][0];
    indexada(x,y,0,1) = v_paleta[index(x,y)][1];
    indexada(x,y,0,2) = v_paleta[index(x,y)][2];
  }
  indexada.display();

  return 0;
}
