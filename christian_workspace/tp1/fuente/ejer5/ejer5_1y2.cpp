//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================

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
	imagen.load(
			"/home/christian/Documentos/universidad/2010/captura/imagenes/rmn.jpg");

	//imagen.get_columns(0,4).display(); // me devuelve desde la fila 0 hasta la columna 4


	CImg<unsigned char> imagen_submuestreada(imagen); //submuestreo sucesivo con un factor de 2
	CImg<unsigned char>
			im1((int) imagen.width() / 2, (int) imagen.height() / 2);

/*
	int matriz [5][5];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			matriz[i][j]=j+2;
			cout<<matriz[i][j]<<"  ";
		}
		cout<<endl;
	}
	cout<<endl;
*/
int x1=0, y1=0;
	cimg_forX(imagen, x){
		if (!(x%2)) continue;
		cimg_forY(imagen, y){
			if (!(y%2)) continue;
			im1(x1,y1)=imagen(x,y);
			y1++;
		}
		x1++;
	}
/*	CImg<unsigned char> m(5,5,1,1);
	cimg_forX(m, x){
		if (!(x%2)) continue;
		cimg_forY(m,y){
			cout<<matriz[x][y]<<"  ";
		}
		cout<<endl;
	}*/
	/*
	int aux = 0;
	int aux1=0;
	for (int x = 0; x < (int) ((imagen)._width); ++x) {
		aux1=0; ++aux;
		if (x % 2)
			continue;
		for (int y = 0; y < (int) ((imagen)._height); y++) {
			im1(aux, aux1) = imagen(x, y);
			++aux1;
			++y;
		}
	}
	im1.display();
*/

	cout << "alto: " << imagen._width << "          ancho: " << imagen._height;

	/*	const int factor = 2;
	 imagen_submuestreada.resize((int) (imagen.width() / factor),
	 (int) (imagen.height() / factor));*/

	//lo de arriba es lo mismo que hacer lo que esta aca abajo:

	//imagen_submuestreada.resize(50, 50).display();

	//resize(100,100) // no tiene efecto alguno sobre la imagen?????-???
	//resize(300,300)  //agranda a 300 x 300...
	//resize(50,50)  //la deja de 50 x 50 etc.

	/*	CImgDisplay vent1(imagen, "imagen con parametro 1", 1), vent2(imagen,
	 "imagen con parametro 0", 0),
	 vent3(imagen, "imagen sin parametro"), vent4(imagen_submuestreada,
	 "imagen con resize", 1);
	 imagen_submuestreada.display("con el mismo factor que la anterior");
	 while (!vent1.is_closed() && !vent2.is_closed() && !vent3.is_closed()
	 && !vent4.is_closed()) {
	 }*/

	return 0;
}
