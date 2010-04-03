#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": visualiza y muestra informacion de la imagen.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    cimg_usage("\n(Probando cimg_usage)");

    return 0;
  }

  // 1. Cargar la imagen
  CImg<unsigned char> imagen( argv[1] );

  // 2. Visualizarla
  imagen.display();

  // 3. Mostrar estadisticas
  imagen.print();
  // imagen.print() me da la misma info que cuando hago display()

  //imagen.stats();
  // imagen.stats() me devuelve un vector tipo CImg con
  // las propiedades de la imagen. Esto lo puedo ver haciendo
  // imagen.get_stats().display();
  // seg'un la documentaci'on, este vector es
  // min,max,mean,variance,xmin,ymin,zmin,cmin,xmax,ymax,zmax,cmax

 
  // Intento mostrar la misma imagen varias veces en una misma ventana
  // usando CImgList

  CImgList<unsigned char> lista(3,imagen);
  lista.display();

  return 0;
}
