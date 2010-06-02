#define UNICODE
#include <CImg.h>
#include <vector>
#include "comun.cpp"
#include "CPDSI_functions.h"

using namespace cimg_library;
using namespace std;


int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    printf("%s: crea un degradé de grises y le asigna la paleta pasada como parámetro.\n", argv[0]);
    printf("uso: %s <archivo_paleta>\n",argv[0]);
    return 1;
  }

  vector<vector<float> > v_paleta;
  cargar_paleta( v_paleta, argv[1] );

  CImg<double> degrade( 256, 256, 1, 3 );
  unsigned x,y;
  cimg_forXY(degrade, x, y) {
    degrade(x,y,0) = v_paleta[x][0];
    degrade(x,y,1) = v_paleta[x][1];
    degrade(x,y,2) = v_paleta[x][2];
  }

  degrade.display();

  return 0;
}


