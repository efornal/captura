/**
 * POSTA: a todos los filtrados (al menos en segmentacion)
 * le aplicamos abs(), es la forma correcta de verlos.
*/

#define pdi_segmentacion 1
#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#include <masks.h>
#include <vector>
#include <list>
#include <iostream>

using namespace std;
using namespace cimg_library;


CImg<double> filtrado_roberts( CImg<double> img ) {
    return 
        img.get_convolve( masks::roberts_gx() ).abs() +
        img.get_convolve( masks::roberts_gy() ).abs();
}

CImg<double> filtrado_prewitt( CImg<double> img ) {
    return 
        img.get_convolve( masks::prewitt_gx() ).abs() +
        img.get_convolve( masks::prewitt_gy() ).abs() +
        img.get_convolve( masks::prewitt_gxy() ).abs() +
        img.get_convolve( masks::prewitt_gyx() ).abs();
}

CImg<double> filtrado_sobel( CImg<double> img ) {
    return 
        img.get_convolve( masks::sobel_gx() ).abs() +
        img.get_convolve( masks::sobel_gy() ).abs() +
        img.get_convolve( masks::sobel_gxy() ).abs() +
        img.get_convolve( masks::sobel_gyx() ).abs();
}

CImg<double> filtrado_laplaciano_g( CImg<double> img ) {
    return img.get_convolve( masks::laplaciano_g() ).abs();
}


/**
 * Transformada Hough directa
 *
 * tomada de funciones de la catedra
 *
 *                        alto                  alto
 * escala rho = ---------------------------  = ------
 *              2 * sqrt{ alto^2 + ancho^2 }   2sqrt{D}
 *
 * NOTA: D = sqrt{ alto^2 + ancho^2 }, se multiplica por 2
 * para armar el acumulador con parte positiva y negativa
 * 
 * escala theta = ancho / pi

 * M_PI = valor de pi, puede definirse si no esta como:
 * ifndef...define M_PI           3.14159265358979323846
 *
 */            
template<class T>
CImg<T> hough_directa( CImg<T> img ) {

    CImg<double> iHough(img);

    // genera espacio parametrico mediante valores equiespaciados 
    // de p y rho inicializandolo en cero(acumulador)
    iHough.fill(0.0); 
    const unsigned M = img.width(), N = img.height();
    int r; // radio mapeado en los N pixeles

    // maximo valor posible de radio se da en la diagonal pcipal
    double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))), 
        step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho])
        step_theta = M_PI / (M - 1), //paso en eje theta (M_PI=pi) (theta=[-90,90])
        rho, theta;
    
    cimg_forXY(img,x,y) {
        if ( img(x, y) > 0.5 )
            //calculo rho variando theta en _todo el eje, con x e y fijo
            for (int t = 0; t < M; t++) { 
                theta = t * step_theta - M_PI / 2; // mapea [0,M] en [-90,90]
                rho = x * cos(theta) + y * sin(theta); // calcula rho
                r = int((rho + max_rho) / step_rho); // mapea [-max_rho , max_rho] en [0,N]
                iHough(t, r) += 1; // suma el acumulador
            }
    }
    return iHough;
}

/**
 * Transformada Hough inversa
 *
 * tomada de funciones de la catedra
 */
template<class T>
CImg<T> hough_inversa( CImg<T> img ) {

    const double blanco[1] = { 255.f };
    CImg<double> iHoughI(img);
    iHoughI.fill(0.0);
    int M = img.width(), 
        N = img.height(), 
        y0, y1;

    //maximo valor posible de radio se da en la diagonal pcipal
    double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))),
        step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho])
        step_theta = M_PI / (M - 1), //paso en eje theta (M_PI=pi) (theta=[-90,90])
        rho, theta;

    cimg_forXY(img,t,r) {
        if ( img(t, r) > 0.5 ) {
            theta = t * step_theta - M_PI / 2; // mapea [0,M] en [-90,90]
            rho = r * step_rho - max_rho; // mapea [0,N] en [-max_rho,max_rho]
            y0 = int(rho / sin(theta));
            y1 = int(rho / sin(theta) - M / tan(theta));
            iHoughI.draw_line(0, (int) y0, (int) M, (int) y1, blanco);
        }
    }
    return iHoughI;
}


/**
 * Filtra la matriz de hough para valores de theta
 * igual al especificado (mas/menos una tolerancia).
 * es decir: Deja solo lineas con un angulo de inclinacion
 * igual al especificado mas/menos una tolerancia
 * El angulo debe estar entre +-pi/2, (en radianes)
*/
template<class T>
CImg<T> filtrar_hough_theta( CImg<T> hough,
                       double u_theta,
                       double tol_theta) {
 
    int M = hough.width(), 
        N = hough.height();
    double theta, step_theta;

    step_theta = M_PI / (M - 1); //paso en eje theta (M_PI=pi) (theta=[-90,90]) */

    cimg_forXY(hough,t,r) {
        theta = t * step_theta - M_PI / 2;
        if ( sqrt( pow(theta-u_theta,2) ) <= tol_theta ) {
            /* printf("if %f <= %f   => %f   tomo: %f \n", */
            /*        sqrt( pow(theta-u_theta,2) ) , */
            /*        tol_theta, */
            /*        hough(t,r), */
            /*        theta ); */
        } else {
            hough(t,r) = 0;
            /* printf("if %f <= %f   => %f   tomo: %f \n", */
            /*        sqrt( pow(theta-u_theta,2) ) , */
            /*        tol_theta, */
            /*        hough(t,r), */
            /*        theta ); */
        }
    }
    return hough;
}

/**
 * Filtra la matriz de hough para valores de rho
 * igual al especificado (mas/menos una tolerancia).
 *
 * Es decir: Permite definir la posicion de la recta
 * en el plano x-y. mas/menos una tolerancia (no el largo!)
*/
template<class T>
CImg<T> filtrar_hough_rho( CImg<T> hough,
                       double u_rho,
                       double tol_rho) {
 
    int M = hough.width(), 
        N = hough.height();
    double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))),
        step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho])
        rho;

    cimg_forXY(hough,t,r) {
        rho = r * step_rho - max_rho; // mapea [0,N] en [-max_rho,max_rho]
        if ( sqrt( pow(rho-u_rho,2) ) <= tol_rho ) {
            /* printf("if %f <= %f   => %f   tomo: %f \n", */
            /*        sqrt( pow(rho-u_rho,2) ) , */
            /*        tol_rho, */
            /*        hough(t,r), */
            /*        rho ); */
        } else {
            hough(t,r) = 0;
            /* printf("if %f <= %f   => %f   tomo: %f \n", */
            /*        sqrt( pow(rho-u_rho,2) ) , */
            /*        tol_rho, */
            /*        hough(t,r), */
            /*        rho ); */
        }
    }
    return hough;
}

/**
 * Filtra la matriz de hough para valores de rho y theta
 * igual al especificado (mas/menos una tolerancia).
 *
 * Es decir: Permite definir la posicion (no el largo!) de la recta
 * en el plano x-y y el angulo de la misma, mas/menos una tolerancia
 *
 * para combinaciones usar  funciones combinadas 
 * (coomo lo hace esta)
*/
template<class T>
CImg<T> filtrar_hough( CImg<T> hough,
                       double u_rho,
                       double u_theta,
                       double tol_rho,
                       double tol_theta) {
    return filtrar_hough_rho( filtrar_hough_theta( hough, u_theta, tol_theta),
                              u_rho, tol_rho );
}

/**
 * Filtra la matriz de hough para valores de rho
 * mayores o iguales al especificado.
 * es decir: Toma solo las linas hubicadas de una determinada
 * posicion(umbral) en la imagen, en adelante
*/
template<class T>
CImg<T> filtrar_hough_rho_min( CImg<T> hough,
                       double u_rho) {
 
    int M = hough.width(), 
        N = hough.height();
    double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))),
        step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho])
        rho;

    cimg_forXY(hough,t,r) {
        rho = r * step_rho - max_rho; // mapea [0,N] en [-max_rho,max_rho]
        if ( abs(rho) >= u_rho ) {
            hough(t,r) = 0;
        }
    }
    return hough;
}

/**
 * Filtra la matriz de hough para valores de rho
 * menores o iguales al especificado.
 *
 * es decir: Toma solo las linas hubicadas de una determinada
 * posicion(umbral) en la imagen, hacia atrás. (hasta el umbral)
*/
template<class T>
CImg<T> filtrar_hough_rho_max( CImg<T> hough,
                       double u_rho) {
 
    int M = hough.width(), 
        N = hough.height();
    double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))),
        step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho])
        rho;

    cimg_forXY(hough,t,r) {
        rho = r * step_rho - max_rho; // mapea [0,N] en [-max_rho,max_rho]
        if ( abs(rho) <= u_rho ) {
            hough(t,r) = 0;
        }
    }
    return hough;
}



/**
 * solo maximos de la t hough
 * FIXME: para valores menores que uno no va detectarlos
 * o va detecta el mismo q esta usando para marcar..
 * se podria usar valores negativos???
 */
template <class T>
CImg<T> get_solo_maximos( CImg<T> img, int cantidad=1 ) {

    CImg<T> maximos(cantidad,1,1,1,0);
    CImg<T> aux(img);
    int cont = 0;
    for ( int i = 0; i < cantidad; i++ ) {
        maximos(cont++) = img.max();
        img.max() = 1;
    }
    cimg_forXY(img,x,y){
        if ( img(x,y) == aux(x,y) ) img(x,y) = 0;
    }
    return img;
}


/**
 *    Procedimiento para crecimiento de regiones:
 * 
 *    region_growing(nodo, propiedad, etiqueta){
 *      if (nodo NO verifica propiedad) return;
 *      if (nodo etiquetado) return;
 *      etiquetar nodo;
 *      region_growing(nodo derecho, propiedad, etiqueta);
 *      region_growing(nodo izquierdo, propiedad, etiqueta);
 *      region_growing(nodo superior, propiedad, etiqueta);
 *      region_growing(nodo inferior, propiedad, etiqueta);
 *    }
 */
/**
 * segmenta una imagen segun la semilla inicial x,y, 
 * con una cierta tolerancia y usa 4 vecinos para la comparacion
 *
 * @param: x_inicial: posicion en x del pixel a segmentar
 * @param: y_inicial: posicion en y del pixel a segmentar
 * @param: intensidad: intensidad del pixel a segmentar
 * @param: widht: ancho de la imagen pasada como parametro
 * @param: height: alto de la imagen pasada como parametro
 * @param: tolerancia: tolerancia con la que se segmenta intendidad+- tolerancia.
 * @param: imagen: imagen sobre la cual se aplica la segmentacion
 * @param: imagen_segmentada: imagen segmentada que es devuelta por referencia. 
 *         (incialmente debe ser una del mismo tamanio que  imagen y rellenada con negro.
 * @param: cant_vecinos(valores aceptados=4 o 8): es la cantidad de vecinos 
 *         que se usan para comparar. 4 por defecto
 * */

template<class T>
void explorar_intensidad( int x_inicial, 
                          int y_inicial, 
                          T intensidad, 
                          int width,
                          int height, 
                          float tolerancia, 
                          CImg<T> &imagen,
                          CImg<T> &imagen_segmentada, 
                          int cant_vecinos = 4) {

    if ( x_inicial > width  - 1 || x_inicial < 0 || 
         y_inicial > height - 1 || y_inicial < 0) {
        return;
    }

    int valor = intensidad - tolerancia;
    if (valor < 0) valor = 0;

    if ( (imagen( x_inicial, y_inicial) <= (intensidad + tolerancia) && 
          imagen( x_inicial, y_inicial) >= valor ) && 
         imagen_segmentada( x_inicial, y_inicial ) == 0) {

        imagen_segmentada( x_inicial, y_inicial ) = 1;

        if ( cant_vecinos == 8 ) { // la diagonal y luego el resto
            //esquina superior izquierda
            explorar_intensidad( x_inicial - 1, y_inicial - 1, intensidad,
                                 width, height, tolerancia, 
                                 imagen, imagen_segmentada);
            //esquina superior derecha 
            explorar_intensidad( x_inicial - 1, y_inicial + 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
            //esquina inferior izquierda
            explorar_intensidad( x_inicial + 1, y_inicial - 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
            //esquina inferior derecha
            explorar_intensidad( x_inicial + 1, y_inicial + 1, intensidad,
                                 width, height, tolerancia, imagen, imagen_segmentada);
        } // si no selecciono los 8 solo hago los 4 vecinos:

        //vecino inferior centro
        explorar_intensidad( x_inicial + 1, y_inicial, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino vecindo derecho centro
        explorar_intensidad( x_inicial, y_inicial + 1, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino superior centro
        explorar_intensidad( x_inicial - 1, y_inicial, intensidad, width,
                             height, tolerancia, imagen, imagen_segmentada);
        //vecino izquierdo centro
        explorar_intensidad(x_inicial, y_inicial - 1, intensidad, width,
                            height, tolerancia, imagen, imagen_segmentada);
    } else {
        return;
    }
}

/** 
 * Funcion wrapper que segmenta una imagen en base al parecido con sus vecinos
 * intensidad del vecino+-tolerancia
 * devuelve una imagen binaria pintada de blanco la parte segmentada.
 * SOLO SIRVE PARA IMAGENES DE 1 solo canal!
 * @param: imagen_a_segmentar: es la imagen sobre la cual se quiere realizar 
 *         la segmentacion
 * @param: x_inicial: posicion en x del pixel a segmentar
 * @param: y_inicial: posicion en y del pixel a segmentar
 * @param: tolerancia: los pixeles segemntados seran aquellos que cumpla con 
 *         intensidad+-tolerancia..
 * @param: cantidad_vecinos(Val. posibles: 4 u 8): cantidad de vecinos usados 
 *         en la segmentacion 4->cruz, 8->_todo el borde
 */
template<class T>
CImg<T> segmentar_binario( CImg<T> imagen_a_segmentar, 
                   int x_inicial, 
                   int y_inicial,
                   float tolerancia = 50.0, 
                   int cantidad_vecinos = 4) {

    int width = imagen_a_segmentar.width();
    int height = imagen_a_segmentar.height();
    T intensidad = imagen_a_segmentar(x_inicial, y_inicial);

    CImg<T> imagen_segmentada ( imagen_a_segmentar.width(),
                                imagen_a_segmentar.height(), 1, 1, 0); //relleno con ceros

    // criterio de segmentacion, modificar para cambiar criterio
    explorar_intensidad ( x_inicial, y_inicial, intensidad, 
                          width, height, tolerancia, 
                          imagen_a_segmentar, imagen_segmentada, cantidad_vecinos );

    return imagen_segmentada;
}

/** 
 * forma la imagen segmentada tomando los tonos de grises de la img original
 * a partir de los valores en la mascara binaria ya segmentada
 *
 * Lo que este blanco en imagen_binaria es remplazado por lo que tenga 
 * la imagen_original y es devuelto en una nueva imagen
 */
template<class T>
CImg<T> binaria_a_grises ( CImg<T> imagen_binaria, CImg<T> imagen_original ) {

    // imagen original rellena con cero de entrada
    CImg<T> imagen ( imagen_original.width(), imagen_original.height(), 1, 1, 0); 

    cimg_forXY( imagen_binaria, x, y ) {
        if ( imagen_binaria(x, y) != 0 ) {
            imagen(x,y) = imagen_original(x,y);
        }
    }
    return imagen;
}

/**
 * Etiquetado de componentes conectadas
 *
 * Retorna una imagen etiquetada por regiones
 * @param CImg<int> img Imagen a partir de la cual se realiza el etiquetado
 *                      Esta imagen debe ser binaria !
 * @param int blanco=1 Intencidad que se considera el blanco (0=negro|1=blanco) 
 * @param int nueva_etiqueta=2 Valor inicial de etiqueta (inicia en 2)
 * @param vector<int> &equivalencias Vector de equivalencias de etiquetas
 * @return CImg<int> Imagen etiquetada por regiones: Una misma region u objeto
 *                   dentro de la imagen, tiene los mismo valores de intencidad
 *                   Por lo tanto: la cantidad diferente de valores (de etiquetas)
 *                   da la cantidad de regiones (u objetos) diferentes que hay 
 */
CImg<int> label_cc( CImg<int> img, 
                    vector<int> &equivalencias,
                    int blanco = 1, 
                    int nueva_etiqueta = 2 ) {

    vector<int> equiv(nueva_etiqueta + 1, 0); //vector de equivalencias
    vector<int> vecinos; //vector de etiquetas vecinos superiores e izquierda
    int pos, etiqueta, aux;

    cimg_forXY(img,x,y) { // recorro la imagen
        if ( img(x,y) == blanco ) { // si es blanco
            vecinos.clear(); // inicializo

            // si x no es borde izq e y no es borde superior miro el vecino sup izq
            if ( x && y )
                if ( img(x-1,y-1) != 0 )
                    vecinos.push_back( img(x-1,y-1) ); // si tiene etiqueta la guardo

            // si y no es borde superior miro vecino superior
            if ( y )
                if ( img(x,y-1) != 0 )
                    vecinos.push_back( img(x,y-1) ); // si tiene etiqueta la guardo

            // si x no es borde derecho e y borde superior miro vecino sup der
            if ( y && x != img.width()-1 )
                if ( img(x+1, y-1 ) != 0 )
                    vecinos.push_back( img(x+1,y-1) ); // si tiene etiqueta la guardo

            // si x no es borde izquierdo miro vecino izq
            if ( x )
                if ( img(x-1,y) != 0 )
                    vecinos.push_back( img(x-1,y) ); // si tiene etiqueta la guardo
            

            // si no tengo vecinos etiquetados debo generar nueva etiqueta
            if ( vecinos.empty() ) { 

                // de vecinos voy a sacar la etiqueta que corresponde al pixel
                vecinos.push_back( nueva_etiqueta ); 

                // guardo en la posicion nva etiqueta el valor nva etiqueta
                equiv[nueva_etiqueta] = nueva_etiqueta;

                nueva_etiqueta++; // genero una nueva etiqueta para cdo necesite
                equiv.push_back( 0 ); // agrego una posicion en equivalencias con 0

            } else {

                for ( int i=0; i<vecinos.size()-1; i++ ) // controlo la lista de etiquetas vecinas

                    // si hay diferentes etiquetas en el vecindario anoto
                    if ( vecinos[i] != vecinos[i + 1]) { 
                        etiqueta = vecinos[i];
                        pos = vecinos[i + 1];

                        // en la pos de la mayor etiqueta anoto el valor de la menor
                        if ( pos < etiqueta ) { 
                            aux = etiqueta;
                            etiqueta = pos;
                            pos = aux;
                        }

                        // si tengo una entrada en esa pos reviso la cadena
                        if ( equiv[pos] != etiqueta ) { 
                            if ( equiv[pos] != pos ) {
                                aux = etiqueta;
                                etiqueta = equiv[pos];
                                pos = aux;
                            
                                while ( equiv[pos] != pos )
                                    pos = equiv[pos];

                                if (equiv[pos] < etiqueta)
                                    etiqueta = equiv[pos];
                            }
                            equiv[pos] = etiqueta;
                        }
                    }
            }
            img(x, y) = vecinos.front(); // asigno etiqueta
        }
    }
    //img.display("Primera Pasada");

    // Muestro como quedo la tabla
    /* cout << "Tabla de equivalencias" << endl << endl; */
    /* for ( int j = 0; j < equiv.size(); j++ ) */
    /*     cout << j << " " << equiv[j] << endl; */
    /* cout << endl; */

    equivalencias = equiv; // retorno la tabla

    // reasigno la etiqueta
    cimg_forXY (img,x,y )
        if ( img(x, y) != 0 )
            if ( equiv[img(x,y)] != img(x,y) ) {
                etiqueta = equiv[img(x, y)];
                while ( equiv[etiqueta] != etiqueta )
                    etiqueta = equiv[etiqueta];
                img(x,y) = etiqueta;
            }
    
    return img;
}

/**
 * Retorna una imagen etiquetada por regiones
 * @param CImg<int> img Imagen a partir de la cual se realiza el etiquetado
 *                      Esta imagen debe ser binaria !
 * @param int blanco=1 Intencidad que se considera el blanco (0=negro|1=blanco) 
 * @param int nueva_etiqueta=2 Valor inicial de etiqueta (inicia en 2)
 * @return CImg<int> Imagen etiquetada por regiones: Una misma region u objeto
 *                   dentro de la imagen, tiene los mismo valores de intencidad
 *                   Por lo tanto: la cantidad diferente de valores (de etiquetas)
 *                   da la cantidad de regiones (u objetos) diferentes que hay 
 */
CImg<int> label_cc( CImg<int> img, 
                    int blanco = 1, 
                    int nueva_etiqueta = 2 ) {
    vector<int> equivalencias; // omito las etiquetas! lo uso solo como fake!
    return label_cc( img, equivalencias, blanco, nueva_etiqueta );
}


// a predicate implemented as a function:
bool igual_a_cero ( const int& value ) { 
    return ( value == 0 ); 
}

/**
 * cuenta la cntidad de regiones que contiene una lista de etiquetas
 * retornada por label_cc
*/
int cantidad_de_regiones(  list<int> etiquetas ){
    etiquetas.sort(); //ordeno lista
    etiquetas.unique(); //borro repetidos
    etiquetas.remove_if( igual_a_cero );
    return etiquetas.size();
}

/**
 * Retorna una imagen etiquetada por regiones
 * @param CImg<int> img Imagen a partir de la cual se realiza el etiquetado
 *                      Esta imagen debe ser binaria !
 * @param int blanco=1 Intencidad que se considera el blanco (0=negro|1=blanco) 
 * @param int nueva_etiqueta=2 Valor inicial de etiqueta (inicia en 2)
 * @return CImg<int> Imagen etiquetada por regiones: Una misma region u objeto
 *                   dentro de la imagen, tiene los mismo valores de intencidad
 *                   Por lo tanto: la cantidad diferente de valores (de etiquetas)
 *                   da la cantidad de regiones (u objetos) diferentes que hay 
 * uso de la lista:
 *  for ( it=mylist.begin() ; it != mylist.end(); it++ )
 *     cout << " " << *it;
 */
CImg<int> label_cc( CImg<int> img, 
                    list<int> &equivalencias,
                    int blanco = 1, 
                    int nueva_etiqueta = 2 ) {
    vector<int> equiv; // omito las etiquetas! lo uso solo como fake!
    img = label_cc( img, equiv, blanco, nueva_etiqueta );
    for ( int s= 0; s < equiv.size(); s++ ){
        equivalencias.push_back( equiv[s] );
    }
    return img;
}






/// usando como base la de hough inversa,. no funciona?
/* template<class T> */
/* CImg<T> filtrar_hough_theta( CImg<T> iHoughI, */
/*                        double u_theta, */
/*                        double tol_theta) { */
/*    int M = iHoughI.width(),  */
/*         N = iHoughI.height(),  */
/*         y0, y1; */

/*     //maximo valor posible de radio se da en la diagonal pcipal */
/*     double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))), */
/*         step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho]) */
/*         step_theta = M_PI / (M - 1), //paso en eje theta (M_PI=pi) (theta=[-90,90]) */
/*         rho, theta; */

/*     cimg_forXY(iHoughI,t,r) { */
/*         if ( iHoughI(t, r) > 0.5 ) { */
/*             theta = t * step_theta - M_PI / 2; // mapea [0,M] en [-90,90] */
/*             rho = r * step_rho - max_rho; // mapea [0,N] en [-max_rho,max_rho] */

/*             if ( sqrt(theta*theta-u_theta*u_theta) <= tol_theta ) { */
/*                         iHoughI(t,r) = 1; */
/*                         printf("if %f <= %f   => %f \n", */
/*                                abs((theta-u_theta)), */
/*                                tol_theta, */
/*                                iHoughI(t,r) ); */

/*                     } else { */
/*                         iHoughI(t,r) = 0; */
/*                         /\* printf("if %f <= %f   => %f \n", *\/ */
/*                         /\*        abs((theta-u_theta)), *\/ */
/*                         /\*        tol_theta, *\/ */
/*                         /\*        hough(t,r) ); *\/ */

/*             } */
/*         } */
/*     } */
/*     return iHoughI; */
/* } */


/// usando como base la de hough directa,. no funciona?
/* template<class T> */
/* CImg<T> filtrar_hough_theta( CImg<T> hough,  */
/*                        double u_theta,  */
/*                        double tol_theta) { */
 
/*     const unsigned M = hough.width(), N = hough.height(); */
/*     int r; // radio mapeado en los N pixeles */

/*     // maximo valor posible de radio se da en la diagonal pcipal */
/*     double max_rho = sqrt(float(pow(N, 2) + pow(M, 2))),  */
/*         step_rho = 2. * max_rho / (N - 1), //paso en eje rho (rho=[-max_rho , max_rho]) */
/*         step_theta = M_PI / (M - 1), //paso en eje theta (M_PI=pi) (theta=[-90,90]) */
/*         rho, theta; */
    
/*     cimg_forXY(hough,x,y) { */
/*         if ( hough(x, y) > 0.5 ) */
/*             //calculo rho variando theta en _todo el eje, con x e y fijo */
/*             for (int t = 0; t < M; t++) {  */
/*                 theta = t * step_theta - M_PI / 2; // mapea [0,M] en [-90,90] */
/*                 rho = x * cos(theta) + y * sin(theta); // calcula rho */
/*                 r = int((rho + max_rho) / step_rho); // mapea [-max_rho , max_rho] en [0,N] */
/*                 if ( sqrt(theta*theta-u_theta*u_theta) <= tol_theta ) { */
/*                         hough(t,r) = 1; */
/*                         printf("if %f <= %f   => %f \n", */
/*                                abs((theta-u_theta)), */
/*                                tol_theta, */
/*                                hough(t,r) ); */

/*                     } else { */
/*                         hough(t,r) = 0; */
/*                         /\* printf("if %f <= %f   => %f \n", *\/ */
/*                         /\*        abs((theta-u_theta)), *\/ */
/*                         /\*        tol_theta, *\/ */
/*                         /\*        hough(t,r) ); *\/ */

/*                     } */
                
/*             } */
/*     } */
/*     return hough; */
/* } */
