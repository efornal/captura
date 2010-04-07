//TODO: hacerlo pero con draw_line.. terminarlo ...
//============================================================================
// Name        :
// Author      : Christian Pfarher
// Version     :
// Copyright   : GNU Public License
// Description : Captura 2010, Ansi-style
//============================================================================
/*	 # grafica los valores de la fila completa de la image seleccionada
 con el mouse.*/
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

struct punto { //define un punto
	int x; //coordenada x
	int y; //coordenada y
} p1, p2;

void construir_eje(int x1, int x2, int *ejex) {
	// construye el eje entre 2 numeros..
	int j = x1;
	int tam = abs(x2 - x1);
	if (x2 > x1) {
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	for (int i = 0; i <= tam - 1; i++) {
		ejex[i] = j++;
		//cout << ejex[i] << "  ";
	}
}

void imprimir_vector(int *vector, int tam) {
	for (int i = 0; i < tam; i++) {
		std::cout << vector[i] << ", ";
	}
}

void evaluar(int x0, int y0, int x1, int y1, int *ejex, int *salida) {
	//evalua una funcion
	int tam = abs(x1 - x0);
	for (int i = 0; i < tam - 1; i++) {

		if ((y1 - y0) != 0) {
			salida[i] = (((x1 - x0) / (y1 - y0)) * (ejex[i] - x0)) + y0;
		} else
			salida[i] = 0; // entonces es 0..
		if (salida[i] < 0)
			salida[i] *= -1; // cuando es menos de un pixel

		cout << endl << "(" << ejex[i] << ", " << salida[i] << ")" << endl;
	}
}

int main(int argc, char *argv[]) {
	CImg<unsigned char> imagen("../../imagenes/parrot.tif");
	CImg<unsigned char> vent_grafico(imagen._width, imagen._height, 1, 3, 0);
	//	CImg<unsigned char> vent_grafico(500, 400, 1, 3, 0);
	imagen.blur(2.5);

	const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 },
			blue[] = { 0, 0, 255 }, blanco[] = { 255, 255, 255 };

	CImgDisplay vent_principal(imagen, "clicken en el primer punto"),
			draw_disp(vent_grafico, "Intensity profile");

	bool presiono = false;

	while (!vent_principal.is_closed() && !draw_disp.is_closed()) { // mientras no cierra nada
		vent_principal.wait(); // espera un evento
		if (vent_principal.button() && vent_principal.mouse_y() >= 0
				&& vent_principal.mouse_x() >= 0 /*&& !two_click*/) { // si hay un evento de raton y Y es >=0 ..

			if (!presiono) {
				p1.x = vent_principal.mouse_x(); //coordenada x del mouse
				p1.y = vent_principal.mouse_y(); //retorna la coordenada en Y del mouse
				cout << endl << "Primer punto (x0, y0) = " << p1.x << ", "
						<< p1.y << endl;
				presiono = !presiono; //ya entro
			}

			else {//ya preciono una vez
				p2.x = vent_principal.mouse_x();
				p2.y = vent_principal.mouse_y();
				cout << "Segundo punto (x1, y1) = " << p2.x << ", " << p2.y
						<< endl;
				imagen.draw_line(p1.x, p1.y, p2.x, p2.y, blanco, 1);

				//esto es para que se vea la linea donde hizo los clicks:

				imagen.display();
				vent_grafico.fill(0); //fondo negro;
				/*imagen.get_crop(p1.x, p1.y, 0, 0, imagen.width() - 1, p1.y, 0,
				 0).display(); //fila 0, y donde clieckee - toda la fila (imagen.width()-1)*/

				vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 1, p2.x,
						p2.y, // una fila!
						0, 1), red, 1, 1, 1, 255, 0);
				vent_grafico.display(draw_disp);

				/*			//                                     width, height, dept, spec, data,
				 vent_grafico.draw_graph(imagen.get_lines(p1.y, p2.y), red, 1,
				 3, 0, 255, 0); // canal red (el espectrum esta en 0 cuando hago el get_crop)
				 //							   |-->plot type=3=bars


				 vent_grafico.draw_graph(imagen.get_lines(p1.y, p2.y), green, 1,
				 1, 0, 255, 0);//|---> canal green (el espectrum esta en 1 cuando hago el get_crop)


				 vent_grafico.draw_graph(imagen.get_lines(p1.y, p2.y), blue, 1,
				 1, 0, 255, 0).display(draw_disp);//|---> canal blue (el espectrum esta en 2 cuando hago el get_crop)

				 //                     color,op,pt,ver,ymin,ymax
				 vent_grafico.draw_graph(imagen, red, 1, 1, 0, 0);*/
			}
		}
	}
	return 0;
}
