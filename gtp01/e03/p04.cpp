#include <CImg.h>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {
    unsigned char rojo[] = {255,0,0};
    int punto1[2] = {-1,-1}, punto2[2] = {-1,-1};
    CImg<unsigned char> img1("../../imagenes/snowman.png");
    CImg<unsigned char> grafica(img1.width(),100,1,1);

    CImgDisplay disp( img1, "Seleccion de fila" );
    CImgDisplay disp_grafica( grafica, "Grafica" );

    while ( !disp.is_closed() && !disp.is_closed() ) {
        disp.wait();
        if ( disp.button() ) {
            if ( punto1[0] >= 0 ) { 
                if ( punto2[0] < 0) { //solo el 1, => asigno 2
                    punto2[0] = disp.mouse_x();
                    punto2[1] = disp.mouse_y();
                    cout << "2da seleccion: " << punto2[0] << "," << punto2[1] << endl;

                    cout << "graficar!" << endl; 
                    grafica.fill(0); //limpia pantalla
                    grafica.draw_graph( img1.get_crop( punto1[0], 
                                                       punto1[1], 
                                                       0, 
                                                       1,
                                                       punto2[0],
                                                       punto1[1], // una fila!
                                                       0,
                                                       1),
                                        rojo, 1, 1, 1 , 255, 0 );
                    grafica.display( disp_grafica );

                    punto1[0] = -1, punto1[1] = -1;
                    punto2[0] = -1, punto2[1] = -1;
                }
            } else { //primer seleccion
                punto1[0] = disp.mouse_x();
                punto1[1] = disp.mouse_y();
                cout << "1er seleccion: " << punto1[0] << "," << punto1[1] << endl;
            }
        }
    }

    return 0;
}
