/*
 * deteccion altura del vino
 *./main -theta 1.5708 -umbral 1 -f imgs_train/blanco_8.jpg
 *
 * detecion bsae media de la copa alta
 *./view_hough_param -umbral 1 -theta 1.57 -rho 170 -tol_rho 20
 *
 * detecion bsae media de la copa baja
 *./view_hough_param -umbral 1 -theta 1.57 -rho 230 -tol_rho 20
 * (+-)45 => (+-) pi/4  =  (+-)0.78540
 * (+-)90 => (+-) pi/2  =  (+-)1.5708 
 *
 * bordes a 45:  ./p02b_theta -theta 0.78540
 * bordes a 90 (horizontales): ./p02b_theta -theta 1.5700 -umbral 1
*/
#include <CHImg.h>

using namespace cimg_library;
using namespace std;

int main( int argc, char **argv ) {
    const char *filename = cimg_option( "-f",
                                        "../../imagenes/letras1.tif",
                                         "ruta archivo imagen" );
    double rho = cimg_option( "-rho", 100, "valor de modulo" );
    double tol_rho = cimg_option( "-tol_rho", 1.0, "tolerancia al modulo" );
    double theta = cimg_option( "-theta", 0.78540, "valor de angulo" );
    double tol_theta = cimg_option( "-tol_theta", 0.01, "tolerancia al angulo" );
    double umbral    = cimg_option( "-umbral", 10, "umbral puntos" );

    CImgDisplay disp, disp1, disp2, disp3, disp4, disp5, disp6;
    
    CHImg<double> img( filename ),orig(img), 
        img_po ,img_xy, img_hough_fil(img), 
        fil_color(img.width(), img.height(), 1,3,0 );
    img.channel(0);
    img.filtrar_sobel().normalize(0,255);
    img.display(disp);

    img_po = hough_directa( img ).normalize(0,255); 

    // ------------------------ altura dle vino
    int max_altura_vino =0;
    // deteccion altura del vino
    //-theta 1.5708 -umbral 1 -f imgs_train/blanco_8.jpg
    CHImg<double> img_altura_vino = 
        filtrar_hough_theta( img_po, 1.5708, 0.01 );
    img_altura_vino = get_solo_maximos( img_altura_vino, 1 );
    CHImg<double> xy_altura_vino = hough_inversa(  img_altura_vino );
    double max_altura =  xy_altura_vino.max();
    cimg_forXY( xy_altura_vino,x,y){
        if (xy_altura_vino(x,y) == max_altura){
            max_altura_vino = y;
        }
    }
    
    printf("altura vino %d  max %f \n",  max_altura_vino, max_altura );

    // ------------------------ altura media copa alta
    int  max_altura_media_copa_alta  =0;
    // deteccion altura del vino

    // -umbral 1 -theta 1.57 -rho 170 -tol_rho 20
     CHImg<double> img_altura_media_copa_alta = 
         filtrar_hough( img_po, 170, 1.57, 10, 0.01 );
     img_altura_media_copa_alta = 
         get_solo_maximos( img_altura_media_copa_alta, 1 );
     CHImg<double> xy_altura_media_copa_alta = 
         hough_inversa(  img_altura_media_copa_alta );
    double max_alta =  xy_altura_media_copa_alta.max();
    cimg_forXY( xy_altura_media_copa_alta,x,y){
        if (xy_altura_media_copa_alta(x,y) == max_alta){
            max_altura_media_copa_alta = y;break;
        }
    }
    if (max_altura_media_copa_alta < 170 && max_altura_media_copa_alta > 150 ){
        printf("es copa alta: altura media_copa %d \n",  max_altura_media_copa_alta);

        //habria q segmentar el color antes porque varia de posicion, luego
        //hago esto, en principio..:
        int x0=70,y0=140;
        //verifico valores de componenteds de color
        if ( orig(x0,y0,0,0) >200 && orig(x0,y0,0,1)>200 ){
            printf("es blanco\n");

            //comprobacion de nivel del vino:
            //copa alta
            int delta1=160-max_altura_vino;
            if (delta1>(130*50)/100){
                printf("copa alta se paso..\n");
            }else{
                printf("copa alta OK\n");
            }

        } else {
            printf("es tinto\n");
        }

    }

   // ------------------------ altura media copa baja
    int  max_altura_media_copa_baja  =0;
    // deteccion altura del vino

    
    //./view_hough_param -umbral 1 -theta 1.57 -rho 230 -tol_rho 20
     CHImg<double> img_altura_media_copa_baja = 
         filtrar_hough( img_po, 230, 1.57, 10, 0.01 );
     img_altura_media_copa_baja = 
         get_solo_maximos( img_altura_media_copa_baja, 1 );
     CHImg<double> xy_altura_media_copa_baja = 
         hough_inversa(  img_altura_media_copa_baja );
    double max_baja =  xy_altura_media_copa_baja.max();
    //este es el codigo correcto, quedeberia ser
    // cimg_forXY( xy_altura_media_copa_baja,x,y){
    //     if (xy_altura_media_copa_baja(x,y) ==  xy_altura_media_copa_baja.max()){//max_baja){
    //         xy_altura_media_copa_baja.display("EL MAX");printf("eeel max:%n \n",xy_altura_media_copa_baja.max()); //borrar
    //         max_altura_media_copa_baja = y;break;
    //     }
    // }
    // HAGO ESTO PORQUE NO ME TOMA EL MAX DE UNA LINEA!!?, CON ESO ANDA TODO EL RESTO
    cimg_forXY( xy_altura_media_copa_baja,x,y){
        if (xy_altura_media_copa_baja(x,y) >200 ){//max_baja){   //FAKE!! > 200 porq no me toma el max??? raro..
            //            xy_altura_media_copa_baja.display("EL MAX");printf("eeel max:%d  --  %d\n",xy_altura_media_copa_baja.max(),y); //borrar
            max_altura_media_copa_baja = y;break;
        }
    }


    //establecer umbral para baja y alta
        if ( max_altura_media_copa_baja > 200 && max_altura_media_copa_baja < 220){
        printf("es copa baja: altura media_copa %d  \n", 
               max_altura_media_copa_baja);


        //habria q segmentar el color antes porque varia de posicion, luego
        //hago esto, en principio..:
        int x0=75,y0=190;
        //verifico valores de componenteds de color
        if ( orig(x0,y0,0,0) >200 && orig(x0,y0,0,1)>200 ){
            printf("es blanco\n");

            //copa baja
            int delta2=220-max_altura_vino;
            if (delta2 > (175*30)/100 ){
                printf("copa baja se paso..\n");
            }else{
                printf("copa baja OK\n");
            }

        } else {
            printf("es tinto\n");

            //copa baja
            int delta2=220-max_altura_vino;
            if (delta2 > (175*50)/100 ){
                printf("copa baja se paso..\n");
            }else{
                printf("copa baja OK\n");
            }

        }

    }
        //COMENTAR
        printf(".....altura media_copa %d %f \n", 
        max_altura_media_copa_baja);
    //        filtrar_hough( img_po, rho, theta, tol_rho, tol_theta );

        




        //COMENTAR
     xy_altura_vino.display();
     xy_altura_media_copa_alta.display();
     xy_altura_media_copa_baja.display();
     orig.display();
    while ( (!disp.is_closed() &&  !disp.is_keyQ()) ) {
        disp.wait_all();
    }
    return 0;
}
