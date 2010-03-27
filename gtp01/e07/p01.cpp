/**
FIXME: como se escala el nivel de gris de la imagen 
para que ocupe el rango completo de medios tonos?
*/
#include <CImg.h>
#include <iostream>

using namespace std;
using namespace cimg_library;

/**
   pinta el cuadro segun la tonalidad, 
   mas puntos negros o blancos segun
*/
void pintar( CImg<unsigned char>& cuadro,int tipo ){

    switch(tipo){
    case 0:
        // no toca, es negro
        break;
    case 1:
        cuadro(1,0) = 255; 
        break;
    case 2:
        cuadro(1,0) = 255;
        cuadro(2,2) = 255;
        break;
    case 3:
        cuadro(0,0) = 255;
        cuadro(1,0) = 255;
        cuadro(2,2) = 255;
        break;
    case 4:
        cuadro(0,0) = 255;
        cuadro(1,0) = 255;
        cuadro(2,2) = 255;
        cuadro(0,2) = 255;
        break;
    case 5:
        cimg_forXY( cuadro, x, y) { cuadro(x,y) = 255; }
        cuadro(0,1) = 0;
        cuadro(1,1) = 0;
        cuadro(2,1) = 0;
        cuadro(2,2) = 0;
        break;
    case 6:
        cimg_forXY( cuadro, x, y) { cuadro(x,y) = 255; }
        cuadro(0,1) = 0;
        cuadro(1,1) = 0;
        cuadro(1,2) = 0;
        break;
    case 7:
        cimg_forXY( cuadro, x, y) { cuadro(x,y) = 255; }
        cuadro(0,1) = 0;
        cuadro(1,1) = 0;
        break;
    case 8:
        cimg_forXY( cuadro, x, y) { cuadro(x,y) = 255; }
        cuadro(1,1) = 0;
        break;
    case 9:
        cimg_forXY( cuadro, x, y) { cuadro(x,y) = 255; }
        //cuadro.display();  //ES NEGRO PORQUE!!!
    };
}

/**
   Asigna un tono de color segun el valor de la imagen
*/
CImg<unsigned char> tono( int valor ) {
    CImg<unsigned char> cuadro( 3, 3, 1, 1, 0 );
    int parte = 256 / 10;
    if( valor < parte) {
        // si es mayor a 9*parte => no hace nada(todo negro)
        pintar( cuadro, 0 ); 
    } else if( valor < 2*parte) {
        pintar( cuadro, 1 ); 
    } else if( valor < 3*parte) {
        pintar( cuadro, 2 ); 
    } else if( valor < 4*parte) {
        pintar( cuadro, 3 ); 
    } else if( valor < 5*parte) {
        pintar( cuadro, 4 ); 
    } else if( valor < 6*parte) {
        pintar( cuadro, 5 ); 
    } else if( valor < 7*parte) {
        pintar( cuadro, 6 ); 
    } else if( valor < 8*parte) {
        pintar( cuadro, 7 ); 
    } else if( valor < 9*parte) {
        pintar( cuadro, 8 ); 
    } else if( valor < 10*parte) {
        pintar( cuadro, 9 ); 
    }


    return cuadro;
}

/**
   Convierte la imagen pasada a una de medios tonos
*/
 CImg<unsigned char> to_medio_tono( CImg<unsigned char> img ){

    CImg<unsigned char> mediotono( 3*img.width(), 3*img.height(), 1, 1 );
    cimg_for_insideXY( img, x, y, 1 ) {
        CImg<unsigned char> cuadro = tono(img(x,y));
        mediotono( 3*x,   3*y )   = cuadro(0,0);
        mediotono( 3*x,   3*y+1 ) = cuadro(0,1);
        mediotono( 3*x,   3*y+2 ) = cuadro(0,2);
        mediotono( 3*x+1, 3*y )   = cuadro(1,0);
        mediotono( 3*x+1, 3*y+1 ) = cuadro(1,1);
        mediotono( 3*x+1, 3*y+2 ) = cuadro(1,2);
        mediotono( 3*x+2, 3*y )   = cuadro(2,0);
        mediotono( 3*x+2, 3*y+1 ) = cuadro(2,1);
        mediotono( 3*x+2, 3*y+2 ) = cuadro(2,2);
    }
    return mediotono;
}

void test_cuadros() {
    CImg<unsigned char> cuadro( 3, 3, 1, 1, 0 );
    for(int i = 0;i<10;i++){
        pintar(cuadro,i);
          cuadro.display();
    }
}

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", 
                                        "../../imagenes/clown.jpg", 
                                        "ruta archivo imagen" );
    const int mostrar = cimg_option( "-p", 0, "mostrar imagen intermedia (!=0)"); 

    CImg<unsigned char> img1( filename );
    CImgDisplay disp, disp2;

    img1.display(disp);

    CImg<unsigned char> mediotono = to_medio_tono( img1 );

    if ( mostrar != 0 ) mediotono.display(disp2);

    mediotono.resize( (int)(mediotono.width()/3), (int)(mediotono.height()/3) );
    mediotono.display();

    while ( !disp.is_closed() && !disp.is_keyQ() ) {}
    return 0;
}
