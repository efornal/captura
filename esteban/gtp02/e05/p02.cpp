/**
   FIXME: or no funciona ???, 
     segun como esta en el libro, para un or deberia verse la parte
     del cuadrado y la der circulo mas la interseccion.
*/
#include <CImg.h>
#include <operadores_logicos.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {

    unsigned char color[] = {255,255,255};
    CImg<unsigned char> circulo( 400, 400, 1, 1, 0 );
    CImg<unsigned char> cuadrado( 400, 400, 1, 1, 0 );
    CImgDisplay disp, disp2, disp3;
    circulo.draw_circle( 150, 200, 60, color );
    cuadrado.draw_rectangle( 150, 150, 300, 300, color );

    circulo.display(disp);
    cuadrado.display(disp2);
    NOT(cuadrado).display("NOT de cuadrado");
    AND(circulo,cuadrado).display("circulo AND cuadrado");
    AND(cuadrado,circulo).display("cuadrado AND circulo");
    OR(circulo,cuadrado).display("circulo OR cuadrado");
    OR(cuadrado,circulo).display("cuadrado OR circulo");
    XOR(circulo,cuadrado).display("circulo XOR cuadrado");
    XOR(cuadrado,circulo).display("cuadrado XOR circulo");
    NOTAND(circulo,cuadrado).display("circulo NOTAND cuadrado");
    NOTAND(cuadrado,circulo).display("cuadrado NOTAND circulo");

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {}
    return 0;
}
