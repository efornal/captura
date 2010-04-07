//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

/* POSTA: El resize se puede coinciderar como un submuestreo, el tema es que dependiendo del tamanio de imagen
 * no necesariamente me va a estar sacando una fila y una columna cada un pixel...
 * resize(50,50) -> reduce en un 50% la imagen (es decir que la nueva va  a ser del 50% de la original en tamanio)
 * resize(100,100) -> no tiene efecto sobre la imagen
 * */
//TODO: terminar el ejercicio con submuestreo "a pata"
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

int main(int argc, char *argv[]) {
	CImg<unsigned char> imagen;
	imagen.load("../../imagenes/rmn.jpg");

	imagen.display("imagen original");
	cout << "Original Size: " << imagen.width() << " x " << imagen.height()
			<< endl;

	CImg<unsigned char> im_submuestreada((int) imagen.width() / 2,
			(int) imagen.height() / 2);

	cout << "SubSample Size: " << im_submuestreada.width() << " x "
			<< im_submuestreada.height();

	int xn = 0, yn = 0;
	cout << endl;
	cimg_forX(imagen, x) {
		if (!(x % 2))
		continue;
		cout << x << " ";
		++xn;
		cimg_forY(imagen, y) {
			//if (!x%2) break;
			im_submuestreada(xn, yn) = imagen(x, y++);
			cout << y << "   ";
			++yn;
		}
		cout << endl;
	}
	im_submuestreada.display();

	return 0;
}
