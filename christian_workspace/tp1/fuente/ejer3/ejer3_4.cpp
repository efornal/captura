//FIXME: esto funciona pero no se si esta bien sacado _todo el tema de la ecuacion de la recta y demas
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

	imagen.blur(2.5);

	const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 },
			blue[] = { 0, 0, 255 };

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

				vent_grafico.fill(0); //fondo negro;

				int tamanio = abs(p2.x - p1.x);
				int eje[tamanio];

				construir_eje(p1.x, p2.x, eje);
				int salida[tamanio];
				evaluar(p1.x, p1.y, p2.x, p2.y, eje, salida);
				cout << "ejex" << endl;
				imprimir_vector(eje, tamanio);
				cout << "ejey" << endl;
				imprimir_vector(salida, tamanio);

				CImg<unsigned char> im1(tamanio, 1,1,1);

				cimg_forX(im1, x){
					im1(x)=imagen(eje[x],salida[x]);
					//cout<<"im("<<x<<")="<<"salida["<<x<<"]="<<salida[x];
				}

				vent_grafico.draw_graph(im1, red, 1,1,0,0);
				 //imagen.get_crop(p1.x, p1.y, 0, 0, p2.x, p2.y, 0, 0).display();

				 //v=0 ; obtengo color rojo
				 //v=1 ; obtengo color verde
				 //v=2 ; obtengo color azul
/*				 vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 0, p2.x,
				 p2.y, 0, 0), red, 1, 1, 0, 255, 0); // canal red (el espectrum esta en 0 cuando hago el get_crop)
				 //					   |-->plot type=3=bars

				 vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 1, p2.x,
				 p2.y, 0, 1), green, 1, 1, 0, 255, 0);//|---> canal green (el espectrum esta en 1 cuando hago el get_crop)


				 vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 2, //|---> canal blue (el espectrum esta en 2 cuando hago el get_crop)
				 p2.x, p2.y, 0, 2), blue, 1, 1, 0, 255, 0).display(
				 draw_disp);*/
				 //                     color,op,pt,ver,ymin,ymax


				 //		two_click = true;
				 //vent_grafico.draw_graph(imagen.get_crop())
				 //draw_graph( data,color,opacity,plot_type,vertex_type,ymin,ymax,expand,pattern)


				 /*     imagen.crop(p1.x,y0,z0,c0,x1,y1,z1,c1);
				 imagen.get_crop(p1.x,y0,z0,c0,x1,y1,z1,c1);
				 \param p1.x = X-coordinate of the upper-left crop rectangle corner.
				 \param y0 = Y-coordinate of the upper-left crop rectangle corner.
				 \param z0 = Z-coordinate of the upper-left crop rectangle corner.
				 \param c0 = C-coordinate of the upper-left crop rectangle corner.
				 \param p2.x = X-coordinate of the lower-right crop rectangle corner.
				 \param p2.y = Y-coordinate of the lower-right crop rectangle corner.
				 \param z1 = Z-coordinate of the lower-right crop rectangle corner.
				 \param c1 = C-coordinate of the lower-right crop rectangle corner.
				 \param border_condition = Dirichlet (false) or Neumann border conditions.
				 *
				 //                                     width, height, dept, spec, data,

				 *
				 # Draw a 1D graph on the instance image.
				 draw_graph( data,color,opacity,plot_type,vertex_type,ymin,ymax,expand,pattern)

				 \param data Image containing the graph values I = f(x).
				 \param color Array of spectrum() values of type \c T, defining the drawing color.
				 \param opacity Drawing opacity.

				 \param plot_type Define the type of the plot :
				 - 0 = No plot.
				 - 1 = Plot using segments.
				 - 2 = Plot using cubic splines.
				 - 3 = Plot with bars.
				 \param vertex_type Define the type of points :
				 - 0 = No points.
				 - 1 = Point.
				 - 2 = Straight cross.
				 - 3 = Diagonal cross.
				 - 4 = Filled circle.
				 - 5 = Outlined circle.
				 - 6 = Square.
				 - 7 = Diamond.
				 \param ymin Lower bound of the y-range.
				 \param ymax Upper bound of the y-range.
				 \param expand Expand plot along the X-axis.
				 \param pattern Drawing pattern.
				 \note
				 - if \c ymin==ymax==0, the y-range is computed automatically from the input samples.

				 The \ref CImg<\c T> structure contains \a six fields :
				 - \ref width defines the number of \a columns of the image (size along the X-axis).
				 - \ref height defines the number of \a rows of the image (size along the Y-axis).
				 - \ref depth defines the number of \a slices of the image (size along the Z-axis).
				 - \ref spectrum defines the number of \a channels of the image (size along the C-axis).
				 - \ref data defines a \a pointer to the \a pixel \a data (of type \c T).
				 - \ref is_shared is a boolean that tells if the memory buffer \ref data is shared with
				 another image.*/
			}
		}
	}
	return 0;
}
