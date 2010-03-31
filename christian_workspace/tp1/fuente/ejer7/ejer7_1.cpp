//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================


//http://usuarios.multimania.es/explorar/halfto/halfto.htm
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

CImg<unsigned char> generar_patron(int tamanio = 3, int radio = 0.5, int tipo =
		0) {
	CImg<int> imagen(tamanio, tamanio, 1, 1, 1); //inicializamos los pixeles a 0 (fondo blanco)
	int centro = (int) (abs(tamanio) / 2);
	if (radio > centro)
		radio = centro;
	imagen.fill(0); //pinto con negro
	switch (tipo) {
	case 0:
		break;
	case 1:
		imagen(1, 0) = 255;
		break;
	case 2:
		imagen(1, 0) = 255;
		imagen(2, 2) = 255;
		break;
	case 3:
		imagen(1, 0) = 255;
		imagen(2, 2) = 255;
		imagen(0, 0) = 255;
		break;
	case 4:
		imagen(1, 0) = 255;
		imagen(2, 2) = 255;
		imagen(0, 0) = 255;
		imagen(0, 2) = 255;
		break;
	case 5:
		imagen(1, 0) = 255;
		imagen(2, 2) = 255;
		imagen(0, 0) = 255;
		imagen(0, 2) = 255;
		imagen(2, 0) = 255;
		break;
	case 6:
		imagen.fill(255); //pinto blanco
		imagen(0, 1) = 0;
		imagen(1, 1) = 0;
		imagen(1, 2) = 0;
		break;
	case 7:
		imagen.fill(255); //pinto blanco
		imagen(0, 1) = 0;
		imagen(1, 1) = 0;
		break;
	case 8:
		imagen.fill(255); //pinto blanco
		imagen(1, 1) = 0;
		break;
	case 9:
		imagen.fill(255);
		break;
	}

	//	imagen.display();
	return imagen;
}

int seleccionapatron(int min, int max, int cant_patrones_a_usar,
		int valor_pixel) { //funcion muy interesante
	//retorna el patron que debe ser usado segun un valor_pixel
	int intervalo = round((max - min) / (cant_patrones_a_usar));
	//cout<<endl<<"el intervalo es: "<<intervalo<< "          max-min= "<<max-min<<endl;

	switch (1 + (valor_pixel > floor(intervalo + min) + 1) + (valor_pixel
			> floor(2 * intervalo + min + 1)) + (valor_pixel > floor(3
			* intervalo + min + 1)) + (valor_pixel > floor(4 * intervalo + min
			+ 1)) + (valor_pixel > floor(5 * intervalo + min + 1))
			+ (valor_pixel > floor(6 * intervalo + min + 1)) + (valor_pixel
			> floor(7 * intervalo + min + 1)) + (valor_pixel > floor(8
			* intervalo + min + 1)) + (valor_pixel > floor(9 * intervalo + min
			+ 1))) {
	case 1: //esta en el primer intervalo de 0 a (max-min)/cant_patrones_a_usar
		return 0;
		break;
	case 2: // esta en el segundo intevalo de (max-min)/cant_patrones_a_usar a 2*(max-min)/cant_patrones_a_usar
		return 1;
		break;
	case 3:
		return 2;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return 7;
		break;
	case 9:
		return 8;
		break;
	case 10:
		return 9;
		break;
	case 11:
		return 9;
		break;
	}
}

CImg<unsigned char> pasar_a_medios_tonos(CImg<unsigned char> imagen, bool reducir_a_original) {
	//funcion que pasa una imagen en esacla de grises a medios tonos
	// reducir_a_original =1  implica reduccion al tamnio de la imagen original
	int minimo = imagen.min();
	int maximo = imagen.max();
	CImg<unsigned char> medios_tonos(3 * imagen.width(), 3 * imagen._height, 1,
			1);
	cimg_for_insideXY( imagen, x, y, 1 )
		{
			CImg<unsigned char> cuadro = generar_patron(3, 0.5,
					(seleccionapatron(minimo, maximo, 10, imagen(x, y))));
			medios_tonos(3 * x, 3 * y) = cuadro(0, 0);
			medios_tonos(3 * x, 3 * y + 1) = cuadro(0, 1);
			medios_tonos(3 * x, 3 * y + 2) = cuadro(0, 2);
			medios_tonos(3 * x + 1, 3 * y) = cuadro(1, 0);
			medios_tonos(3 * x + 1, 3 * y + 1) = cuadro(1, 1);
			medios_tonos(3 * x + 1, 3 * y + 2) = cuadro(1, 2);
			medios_tonos(3 * x + 2, 3 * y) = cuadro(2, 0);
			medios_tonos(3 * x + 2, 3 * y + 1) = cuadro(2, 1);
			medios_tonos(3 * x + 2, 3 * y + 2) = cuadro(2, 2);
		}
	if (reducir_a_original) return medios_tonos.resize((int) (medios_tonos.width() / 3), (int) (medios_tonos.height() / 3));
	return medios_tonos;
}

int main(int argc, char *argv[]) {

	CImg<unsigned char> imagen("../../imagenes/clown.jpg");
	imagen.display("Pallazo antes del normalizado");
	imagen.normalize(imagen.min(), imagen.max()); //normalizo la imagen entre el valor minimo y maximo
	imagen.display("Pallazo despues del normalizado");
	//imagen.quantize(10); //cuantizo la imagen en 10 niveles de acuerdo a la cantidad de patrones
	imagen.display("Pallazo despues del normalizado y cuantizado");

	pasar_a_medios_tonos(imagen, 0).display("Modificando el tamanio");
	pasar_a_medios_tonos(imagen, 1).display("Resize");

	return 0;
}
