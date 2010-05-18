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
    // if ( d_planos.is_keyARROWDOWN() ) {
    //   plano_actual = max( plano_actual-1, 0 );
    //   planos(plano_actual).display(d_planos);
    // }
    // if ( d_planos.is_keyARROWUP() ) {
    //   plano_actual = min( plano_actual+1, 7 );
    //   planos(plano_actual).display(d_planos);
    // }
    // if ( d_imagen.is_keyARROWDOWN() ) {
    //   n_planos_recon = max( n_planos_recon-1, 1 );
    //   recon = reconstruir( planos.get_images(8-n_planos_recon, 7) ).normalize(0,255);
    //   cout<<"n planos: "<<n_planos_recon<<"; mse: "<<imagen.MSE(recon)<<endl;
    //   recon.display(d_imagen);
    // }
    // if ( d_imagen.is_keyARROWUP() ) {
    //   n_planos_recon = min( n_planos_recon+1, 8 );
    //   recon = reconstruir( planos.get_images(8-n_planos_recon, 7) ).normalize(0,255);
    //   cout<<"n planos: "<<n_planos_recon<<"; mse: "<<imagen.MSE(recon)<<endl;
    //   recon.display(d_imagen);
    // }
  }
  return 0;
}

