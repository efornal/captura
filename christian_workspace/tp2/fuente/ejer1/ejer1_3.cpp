//============================================================================
// Name        : tp2.cpp
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <CImg.h>
using namespace std;
using namespace cimg_library;


CImg<unsigned char> negativo(CImg<unsigned char> & img1)
{	//retorna el negativo de una imagen
	int a=-1;
	unsigned char c=img1.max(); // maximo de la imagen
    CImg<unsigned char> img2(img1.width(), img1.height(), 1, 1);
    cimg_forXY(img2,x,y){
		img2(x,y)=a*img1(x,y)+c;
	}
    return img2;
}

int main() {
	CImg <unsigned char> img1("/home/christian/Documentos/universidad/2010/captura/imagenes/letras1.tif");
    CImg<unsigned char> img2 = negativo(img1);
    CImgDisplay vent1(img1, "imagen original", 1), vent2(img2, "negativo de imagen original", 1);

while(!vent1.is_closed()&& !vent2.is_closed()){}

	return 0;
}
