/**
   A medida que la imagen se complementa con los sucesivos planos,
   7,6,...0, el error cuadratico disminuye, y la imagen se hace
   cada vez mas parecida a la original.
   Para el plano cero y uno (cuando se han sumado la mayoria) 
   el error cuadratico tiende a cero y las imagenes casi no se
   diferencian.
   plano: 3   MSE(Err. Cuad. Medio): 16.896
   plano: 2   MSE(Err. Cuad. Medio): 2.40436
   plano: 1   MSE(Err. Cuad. Medio): 0.342901
   plano: 0   MSE(Err. Cuad. Medio): 0

   DECONSULTA: Los planos de bits superiores (7,6,5) contiene mejor
   informacion de la imagen(mejor representacion) que los planos
   menores (0,1) porque la variacion de estos bits(0-1-0-1..)  
   es alta y se da para todos  los niveles de grises, 
   mientras que para los superiores esta variacion no es tan repetida
   Ej: 001   el ultimo bit varió: (1 0 1) 
       010   
   ... 100 ...  el primero varía menos
*/
#include <CHImg.h>
#include <imagenes.h>
#include<iostream>

using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f", "../../../imagenes/tablero.png", 
                                        "ruta archivo imagen" );

    //CImg<unsigned char> img1 = tonos_de_gris( 255 );
    CHImg<unsigned char> img1( filename );
    CHImg<unsigned char> result;
    CImg<unsigned char> planos[8];
    CImgDisplay disp2( img1, "original" , 1 );

    for ( int i=0; i<8; i++ ) {
        planos[i] = img1.get_plano_de_bit( i ) ;
    }

    result =  planos[7]*pow(2,7);
    CImgDisplay disp( result, "planos de bit - composicion 7->1" , 1 );
    int plano = 7;

    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ){
        
        disp.wait();
        result =  planos[7]*pow(2,7);
    
        if (  disp.is_keyARROWDOWN() ) {
            if ( plano > 0 ) {
                plano--;           
                for ( int i=6;i>=plano;i--){
                    result = result + planos[i]*pow(2,i);
                }
                result.display(disp);
                cout << "plano: " << plano 
                     << "   MSE(Err. Cuad. Medio): " << result.MSE(img1) << endl;
            }
        }
        
        if (  disp.is_keyARROWUP() ) {
            if ( plano < 7 ) {
                plano++;
                for ( int i=6;i>=plano;i--){
                    result = result + planos[i]*pow(2,i);
                }
                result.display(disp);
                cout << "plano: " << plano 
                     << "   MSE(Err. Cuad. Medio): " << result.MSE(img1) << endl;
            }
        }
        
    }
    return 0;
}
