//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================
//FIXME:
/*
 *submuestrear es lo mismo que reducir el tamanio por el factor
 *resize(50,50) es lo mismo que hacer lo otro??
 *resize(100,100) // no tiene efecto alguno sobre la imagen?????-???*/

#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/rmn.jpg");

	imagen.display("imagen original");
	cout<<"Original Size: "<< imagen.width()<< " x "<<imagen.height()<<endl;

	CImg<unsigned char> im_submuestreada((int) imagen.width() / 2, (int) imagen.height() / 2);

	cout<<"SubSample Size: " <<im_submuestreada.width()<< " x "<< im_submuestreada.height();

	int xn=0, yn=0;
cout<<endl;
	cimg_forX(imagen, x){
		if (!(x%2)) continue;
		cout<<x<< " ";
		++xn;
		cimg_forY(imagen, y){
			//if (!x%2) break;
			im_submuestreada(xn,yn)=imagen(x,y++);
			cout<<y<<"   ";
			++yn;
		}
		cout<<endl;
	}
im_submuestreada.display();

	return 0;
}
