#define UNICODE
#include <CImg.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace cimg_library;
using namespace std;

// template<class T>
// T min( T a, T b ) {
//   return (a<b) ? a : b;
// }

/*
 * función bitplanes: recibe una imagen en GRIS 8bits, y devuelve una CImgList
 * de 8 imágenes bool, cada una es el plano de bits de 0 a 7 respectivamente.
 */
CImgList<bool> bitplanes( CImg<unsigned char> &imagen ) {
  unsigned x=0, y=0, p=0;
  unsigned char mascara=1;
  CImg<bool> temp( imagen.width(), imagen.height(), 1, 1, 0); //genero la imagen negra
  CImgList<bool> resultado;
  for ( p=0; p<8; p++ ) {
    resultado.push_back(temp);
    cimg_forXY( imagen, x, y ) {
      resultado(p,x,y) = ( imagen(x,y) & mascara ) > 0 ? 1 : 0 ;
    }
    mascara=mascara<<1;
  }
  return resultado;
}

CImg<unsigned char> reconstruir( CImgList<bool> planos ) {
  CImg<unsigned char> resultado( planos(0).width(), planos(0).height(), 1, 1, 0) ;
  unsigned x=0, y=0, p0=8-min(planos.size(),(unsigned int)8), p=p0; // empiezo contando de 2 si planos tiene 5 imágenes
  unsigned char valor_bit = 1;
  valor_bit = valor_bit<<p; //corro el valor de valor_bit tal que empiece en el p-ésimo lugar
  for ( p; p<8; p++ ) {
    cimg_forXY( resultado, x, y) {
      resultado(x,y) += (unsigned char) planos(p-p0,x,y) * valor_bit;
    }
    valor_bit = valor_bit << 1;
  }
  return resultado;
}

int main(int argc, char *argv[]) {

  if ( !argv[1] ){
    cout<<argv[0]<<": Carga 2 imágenes y aplica umbrales invertidos en ellas.\n";
    cout<<"uso: "<<argv[0]<<" <archivo_imagen0> <archivo_imagen1>"<<endl;
    return 1;
  }

  CImg<unsigned char> imagen( argv[1] );
  CImgList<bool> planos = bitplanes(imagen);

  CImgDisplay d_planos, d_imagen;

  CImg<unsigned char> recon = reconstruir(planos.get_images(7,7));
  imagen.normalize(0,255);

  short plano_actual = 7, n_planos_recon = 1;

  planos(plano_actual).display(d_planos);
  recon.display(d_imagen);
  
  while ( !d_planos.is_closed() && !d_imagen.is_closed() ) {
    d_planos.wait_all();
    if ( d_planos.is_keyARROWDOWN() ) {
      plano_actual = max( plano_actual-1, 0 );
      planos(plano_actual).display(d_planos);
    }
    if ( d_planos.is_keyARROWUP() ) {
      plano_actual = min( plano_actual+1, 7 );
      planos(plano_actual).display(d_planos);
    }
    if ( d_imagen.is_keyARROWDOWN() ) {
      n_planos_recon = max( n_planos_recon-1, 1 );
      recon = reconstruir( planos.get_images(8-n_planos_recon, 7) ).normalize(0,255);
      cout<<"n planos: "<<n_planos_recon<<"; mse: "<<imagen.MSE(recon)<<endl;
      recon.display(d_imagen);
    }
    if ( d_imagen.is_keyARROWUP() ) {
      n_planos_recon = min( n_planos_recon+1, 8 );
      recon = reconstruir( planos.get_images(8-n_planos_recon, 7) ).normalize(0,255);
      cout<<"n planos: "<<n_planos_recon<<"; mse: "<<imagen.MSE(recon)<<endl;
      recon.display(d_imagen);
    }
  }
  return 0;
}

