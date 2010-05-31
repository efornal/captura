#define UNICODE
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": carga una imagen y ecualiza su histograma.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen_intensidad>"<<endl;

    return 0;
  }

  // 1. Cargar las imagenes y crear displays
  CImg<unsigned char> imagen( argv[1] ), grafico(256,256,1,1,192);



  CImgList<unsigned char> imagenes( imagen, imagen.get_equalize(256) ),
    histogramas(grafico.fill(192).draw_graph(imagen.get_histogram(256,0,255)),
		grafico.fill(192).draw_graph(imagen.get_equalize(256).get_histogram(256,0,255)));
  //  CImgDisplay disp_imag(imagenes,"Imagenes"), disp_graf(histogramas,"Histogramas");
  imagenes.display();
  histogramas.display();

  return 0;
}
