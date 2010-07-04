/******************************************************
 *            jpeg
 *
 *  Fri Jun 1 2007
 *  Copyright  2007  Mónica Larese
 *  mlarese@ifir.edu.ar
 *******************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <CImg.h>
#include <sys/stat.h>
#include <algorithm>

using namespace std;
using namespace cimg_library;

class CVariance {
public:
  int index;
  float var;
};

bool compare_variances(const CVariance &a, const CVariance &b) {
  return a.var < b.var;
}

template<class TT>
CImg<TT> jpeg( CImg<TT> img, int sizeblock=8, int N=24 ) {

  const int K = sizeblock * sizeblock - N;
  cout << "Numero de coeficientes a eliminar: " << K << endl;

  img.normalize(0, 1);   //LA NORMALIZA ENTRE 0 Y 1

  CImg<double> original(img);
  original.resize(256, 256, -100, -100, 1);
  original = original - 0.5;   //LA LLEVA AL RANGO -0.5..0.5

  //TAMAÑO DE LA IMAGEN ORIGINAL
  int n = original.width();
  int m = original.height();

  //CANTIDAD DE FILAS Y COLUMNAS DE BLOQUES
  int nblockcols = int(n / sizeblock);
  int nblockrows = int(m / sizeblock);
  int nblocks = nblockcols * nblockrows;

  //Matriz de coeficientes para la transformada coseno
  CImg<double> T(sizeblock, sizeblock, 1, 1, 0);
  for (int q = 0; q < sizeblock; q++) {
    for (int p = 0; p < sizeblock; p++) {
      if (p == 0)
        T(q, p) = 1. / sqrt(sizeblock);
      else
        T(q, p) = sqrt(2. / sizeblock) *
          cos( M_PI * (2. * q + 1. ) * p / (2. * sizeblock) );
    }
  }

  CImg<double> bloques(nblocks, sizeblock * sizeblock, 1, 1, 0);
  CImg<double> block(sizeblock, sizeblock, 1, 1, 0),
    dct_coef(sizeblock,sizeblock, 1, 1, 0);

  //EXTRAE LOS BLOQUES, LE CALCULA A C/U LA DCT Y COLOCA LOS COEFICIENTES EN UNA
  //MATRIZ, DONDE CADA COLUMNA CONTIENE LOS COEFICIENTES DE CADA BLOQUE
  int r = 0;
  for (int i = 0; i < nblockcols; i++) {
    for (int j = 0; j < nblockrows; j++) {
      r++;
      for (int k = 0; k < sizeblock; k++) {
        for (int l = 0; l < sizeblock; l++) {
          block(k, l) = original(i * sizeblock + l, j * sizeblock + k);
        }
      }
      dct_coef = T * block * T.get_transpose();
      int s = 0;
      for (int k = 0; k < sizeblock; k++) {
        for (int l = 0; l < sizeblock; l++) {
          s++;
          bloques(r - 1, s - 1) = dct_coef(k, l);
        }
      }
    }
  }

  //CALCULA LAS VARIANZAS DE LOS COEFICIENTES PARA CADA BLOQUE Y LAS ORDENA
  CImg<double> fila(1, nblocks, 1, 1, 0);
  vector<CVariance> variance(sizeblock * sizeblock);

  for (int i = 0; i < sizeblock * sizeblock; i++) {
    for (int j = 0; j < nblocks; j++)
      fila(0, j) = bloques(j, i);
    CImg<> estad(fila.stats());
    variance[i].index = i;
    variance[i].var = estad(3, 0);
  }

  sort(variance.begin(), variance.end(), compare_variances);

  //ELIMINACION DE LOS K COEFICIENTES CON MENOR VARIANZA
  for (int i = 0; i < K; i++) {
    for (int j = 0; j < nblocks; j++) {
      bloques(j, variance[i].index) = 0;
    }
  }

  // PARA CADA BLOQUE CALCULA LA IDCT CON LOS COEFICIENTES DISTINTOS DE CERO
  // Y COLOCA EL RESULTADO EN LA IMAGEN FINAL
  CImg<double> idct_coef(sizeblock, sizeblock, 1, 1, 0);
  CImg<double> comprimida(n, m, 1, 1, 0);

  r = 0;
  for (int i = 0; i < nblockrows; i++) {
    for (int j = 0; j < nblockcols; j++) {
      r++;
      int s = 0;
      for (int k = 0; k < sizeblock; k++) {
        for (int l = 0; l < sizeblock; l++) {
          s++;
          block(l, k) = bloques(r - 1, s - 1);
        }
      }
      idct_coef = T.get_transpose() * block * T;
      for (int k = 0; k < sizeblock; k++) {
        for (int l = 0; l < sizeblock; l++) {
          comprimida(i * sizeblock + k, j * sizeblock + l) = idct_coef(k, l);
        }
      }
    }
  }

  comprimida += 0.5;
  comprimida.resize(img.width(), img.height(), -100, -100, 1);
  comprimida.normalize(0, 1);

  return comprimida;
}
