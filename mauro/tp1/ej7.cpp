#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen de intensidad y genera una 3x más grande en medios tonos.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<bool> patron(3,3,1,1,0);
  CImgList<bool> patrones(patron);

  //imagen 1
  patron(1,0)=1;
  patrones.insert(patron);

  //imagen 2
  patron(2,2)=1;
  patrones.insert(patron);

  //imagen 3
  patron(0,0)=1;
  patrones.insert(patron);

  //imagen 1
  patron(0,2)=1;
  patrones.insert(patron);

  //imagen 5
  patron(2,0)=1;
  patrones.insert(patron);

  //imagen 6
  patron(2,1)=1;
  patrones.insert(patron);

  //imagen 7
  patron(1,2)=1;
  patrones.insert(patron);

  //imagen 8
  patron(0,1)=1;
  patrones.insert(patron);

  //imagen 9
  patron(1,1)=1;
  patrones.insert(patron);


  CImg<unsigned char> imagen ( argv[1] );
  imagen.display();
  CImg<bool> halftone ( imagen.width()*3, imagen.height()*3, 1, 1);

  imagen.normalize(0,255);

  unsigned x, y, idx;

  cimg_forXY( imagen, x, y) {
    idx = floor( imagen(x,y)/25.6 );
    halftone(3*x,3*y)=patrones(idx,0,0);
    halftone(3*x,3*y+1)=patrones(idx,0,1);
    halftone(3*x,3*y+2)=patrones(idx,0,2);
    halftone(3*x+1,3*y)=patrones(idx,1,0);
    halftone(3*x+1,3*y+1)=patrones(idx,1,1);
    halftone(3*x+1,3*y+2)=patrones(idx,1,2);
    halftone(3*x+2,3*y)=patrones(idx,2,0);
    halftone(3*x+2,3*y+1)=patrones(idx,2,1);
    halftone(3*x+2,3*y+2)=patrones(idx,2,2);
  }

  halftone.display();

  return 0;
}
