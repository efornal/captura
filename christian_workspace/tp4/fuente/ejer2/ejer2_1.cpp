//============================================================================
/*
 * ejer2_1.cpp
 *
 *  Created on: 20/04/2010
 *      Author: christian
 */

//============================================================================
/*	 # grafica los valores de la fila completa de la image seleccionada
 con el mouse.*/
#include <CImg.h>
#include <iostream>
using namespace cimg_library;
using namespace std;

struct punto {
   int x;
   int y;
} p1;


int main(int argc, char *argv[]) {
	CImg<unsigned char>
			imagen(
					"../../imagenes/patron.tif");
	CImg<unsigned char> vent_grafico(500, 400, 1, 3, 0);

	//imagen.blur(2.5);

	const unsigned char red[] = { 255, 0, 0 }, green[] = { 0, 255, 0 },
			blue[] = { 0, 0, 255 };

	CImgDisplay vent_principal(imagen, "clickeame"), draw_disp(vent_grafico,
			"Intensity profile");
	const int fila=0;
	p1.x=fila;
	while (!vent_principal.is_closed() && !draw_disp.is_closed()) { // mientras no cierra nada
		vent_principal.wait(); // espera un evento
		if (vent_principal.button() && vent_principal.mouse_y() >= 0) { // si hay un evento de raton y Y es >=0 ..
			p1.y = vent_principal.mouse_y(); //retorna la coordenada en Y del mouse
			//v=0 ; obtengo color rojo
			//v=1 ; obtengo color verde
			//v=2 ; obtengo color azul
			vent_grafico.fill(0); //fondo negro;

			//vent_grafico.draw_graph(imagen.get_crop())
			//draw_graph( data,color,opacity,plot_type,vertex_type,ymin,ymax,expand,pattern)


			/**     imagen.crop(x0,y0,z0,c0,x1,y1,z1,c1);
			 imagen.get_crop(x0,y0,z0,c0,x1,y1,z1,c1);
			 \param x0 = X-coordinate of the upper-left crop rectangle corner.
			 \param y0 = Y-coordinate of the upper-left crop rectangle corner.
			 \param z0 = Z-coordinate of the upper-left crop rectangle corner.
			 \param c0 = C-coordinate of the upper-left crop rectangle corner.
			 \param x1 = X-coordinate of the lower-right crop rectangle corner.
			 \param y1 = Y-coordinate of the lower-right crop rectangle corner.
			 \param z1 = Z-coordinate of the lower-right crop rectangle corner.
			 \param c1 = C-coordinate of the lower-right crop rectangle corner.
			 \param border_condition = Dirichlet (false) or Neumann border conditions.
			 **/

			imagen.get_crop(p1.x, p1.y, 0, 0, imagen.width() - 1, p1.y, 0, 0); //fila 0, y donde clieckee - toda la fila (imagen.width()-1)
			//                                     width, height, dept, spec, data,
			vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 0, imagen.width()
					- 1, p1.y, 0, 0), red, 1, 3, 0, 255, 0); // canal red (el espectrum esta en 0 cuando hago el get_crop)
			//							   |-->plot type=3=bars

			vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 1, imagen.width()
					- 1, p1.y, 0, 1), green, 1, 1, 0, 255, 0);//|---> canal green (el espectrum esta en 1 cuando hago el get_crop)


			vent_grafico.draw_graph(imagen.get_crop(p1.x, p1.y, 0, 2, imagen.width()//|---> canal blue (el espectrum esta en 2 cuando hago el get_crop)
					- 1, p1.y, 0, 2), blue, 1, 1, 0, 255, 0).display(draw_disp);
			//                     color,op,pt,ver,ymin,ymax
			/**
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
			 */
			/*The \ref CImg<\c T> structure contains \a six fields :
			 - \ref width defines the number of \a columns of the image (size along the X-axis).
			 - \ref height defines the number of \a rows of the image (size along the Y-axis).
			 - \ref depth defines the number of \a slices of the image (size along the Z-axis).
			 - \ref spectrum defines the number of \a channels of the image (size along the C-axis).
			 - \ref data defines a \a pointer to the \a pixel \a data (of type \c T).
			 - \ref is_shared is a boolean that tells if the memory buffer \ref data is shared with
			 another image.*/
		}
	}
	return 0;
}
