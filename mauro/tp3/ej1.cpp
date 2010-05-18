#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Carga una imagen y la muestra junto con la ecualizada, y sus respectivos histogramas.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen>"<<endl;
    return 1;
  }

  CImg<double> imagen( argv[1] );
  CImg<double> histog( 256,256,1,1,80 );

  double color = 255.0;

  CImgList<double> imagens ( imagen, imagen.get_equalize(256) );
  CImgList<double> histogs ( histog.get_fill(80).draw_graph( imagen.get_histogram(256), &color, 1, 3),
			     histog.get_fill(120).draw_graph( imagens(1).get_histogram(256), &color, 1, 3) );

  CImgDisplay d_imgs, d_hist;


  imagens.display( d_imgs);
  histogs.display( d_hist);
  
  while ( !d_imgs.is_closed() && !d_hist.is_closed() ) {
    d_imgs.wait_all();
  }
  return 0;
}

