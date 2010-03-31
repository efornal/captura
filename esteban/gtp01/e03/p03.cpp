/**
   # grafica los valores de la fila completa de la image seleccionada
   con el mouse.

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
#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    unsigned char rojo[] = {255,0,0};
    int plot_type = 1;
    int vertex_type = 1;
    //CImg<unsigned char> img1(400,200,1,1);
    CImg<unsigned char> img1("../../imagenes/earth.bmp");
    CImg<unsigned char> grafica(img1.width(),100,1,1);

    CImgDisplay disp( img1, "Seleccion de fila" );
    CImgDisplay disp_grafica( grafica, "Grafica" );

    while ( !disp.is_closed() && !disp.is_closed() ) {
        disp.wait();
        if ( disp.button() && disp.mouse_y() >= 0 ) {
            //cout << "fila(y):" << disp.mouse_y();
            grafica.fill(0); //limpia pantalla
            grafica.draw_graph( img1.get_crop( 0, 
                                            disp.mouse_y(), 
                                            0, 
                                            1,
                                            img1.width()-1,
                                            disp.mouse_y(),
                                            0,
                                            1),
                                rojo, 1, plot_type, vertex_type , 255, 0 );
            grafica.display( disp_grafica );
        }
    }

    return 0;
}
