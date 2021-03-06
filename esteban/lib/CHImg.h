#define cimg_use_fftw3 1

#ifdef cimg_use_fftw3
extern "C"{
    #include "fftw3.h"
}
#endif

#ifndef pdi_segmentacion
  #include "segmentacion.h"
#endif
#ifndef pdi_restauracion
  #include "restauracion.h"
#endif
#ifndef pdi_espectro
  #include "espectro.h"
#endif
#ifndef pdi_color
  #include "color.h"
#endif

#include <CImg.h>

using namespace cimg_library;

template<typename T> struct CHImg : public CImg<T> {

    // Constructores replicados

    explicit CHImg( const unsigned int dx=0, 
                    const unsigned int dy=1,
                    const unsigned int dz=1, 
                    const unsigned int dv=1 )
        : CImg<T>(dx,dy,dz,dv){};

    explicit CHImg( const unsigned int dx, 
                    const unsigned int dy,
                    const unsigned int dz, 
                    const unsigned int dv, const T& val )
        : CImg<T>(dx,dy,dz,dv,val) {};

    template<typename t> CHImg( const CImg<t>& img )
        : CImg<T>(img) {}

 CHImg( const CImg<T>& img )
     : CImg<T>(img) {}
    
    template<typename t> CHImg( const CImg<t>& img,
                                const bool pixel_copy )
        : CImg<T>(img,pixel_copy) {}
    
 CHImg( const char *const filename )
     : CImg<T>( filename ) {}

    template<typename t> CHImg( const t *const data_buffer,
                                const unsigned int dx, 
                                const unsigned int dy=1,
                                const unsigned int dz=1,
                                const unsigned int dv=1,
                                const bool multiplexed=false )
    : CImg<T>( data_buffer, dx, dy, dz, dv, multiplexed) {}

    // *** nueva funcionalidad ***

    // ------------- Operadores relacionales  ------------- \\

    CImg<unsigned char> menor (  CImg<unsigned char>img2 ) {
        CImg<unsigned char>img1 = *this;
        cimg_forXY( img1, x, y ) {
            img1(x,y) = ( img1(x,y) < img2(x,y) ) ? 0 : 255;
        }
        return img1;
    }

    /**
     * Retorna el plano de bit nro de la imagen
     */
    CImg<unsigned char> get_plano_de_bit( int nro=0 ){
        CImg<unsigned char> img = *this;
        if ( nro > 0 ) {
            cimg_forXY(img,x,y){
                img(x,y) = (img(x,y) >> nro) &0x00000001;
            }
        } else{
            cimg_forXY(img,x,y){
                img(x,y) = (img(x,y)) &0x00000001;
            }
        }
        return img;
    }

    /**
     * Transformacion lineal - Lut: s = ar + c
     */
    CImg<unsigned char> get_lut( int a=1, int c=0 ) {
        CImg<unsigned char> img1 = *this;
        CImg<unsigned char> img2( img1.width(), img1.height(), 1, 1 );
        cimg_forXY( img1, x, y ) {
            img2(x,y) =  a*img1(x,y) + c;
            if ( img2(x,y) > 255 ) img2(x,y) = 255; // clipping
            if ( img2(x,y) < 1   ) img2(x,y) = 0; // clipping
        }
        return img2; 
    }
    
    /**
     * Suma punto a punto de dos imagenes (no promedia)
     */
    void sumar( CImg<double> img2 ) { 
        CImg<double> img1 = *this; 
        cimg_forXY( img1, x, y ) {
            img1(x,y) = ( img1(x,y) + img2(x,y) );
        }
        *this = img1; //rebuscado!
    }
    

    /**
     * Suma punto a punto de dos imagenes (no promedia)
     */
    CImg<double> sumar( CImg<double> img1,CImg<double> img2 ) { 
        cimg_forXY( img1, x, y ) {
            img1(x,y) = ( img1(x,y) + img2(x,y) );
        }
        return img1;
    }

    /**
     * Suma de dos imagenes promediando los valores
     * ej: usada para reduccion de ruido
     */
    void suma_promedio( CImg<double> img2 ) { 
        CImg<double> img1 = *this;
        cimg_forXY( img1, x, y ) {
            img1(x,y) = ( img1(x,y) + img2(x,y) ) / 2.0;
        }
    }

    /**
     * Suma de n imagenes promediando los valores
     * ej: usada para reduccion de ruido
     */
    CImg<double> get_suma_promedio( CHImg<double> imagenes[], int cantidad=0 ) { 
        CHImg<double> promedio;

        promedio = imagenes[0];

        for( int i=1; i<cantidad; i++){
            promedio.sumar(imagenes[i] );
        }

        cimg_forXY( promedio, x, y ) {
            promedio(x,y) = ( promedio(x,y) / (double)cantidad );
        }

        return promedio;
    }
    
    /**
     * Realiza un filtrado de alta potencia - HighBoost usando
     * mascara difusa (con factor variable)
     * g(x,y) = A*f(x,y) - PB{ f(x,y) }
     * Si factor=1 =>  g(x,y) = PA{ f(x,y) }  pasa altos normal
     * Si factor>1 =>  g(x,y) = k*f(x,y) + PA{ f(x,y) } agrega parte baja frec
     * @mask mascara pasa bajos
     * @factor facator  A aplicado a la imagen
     * FIXME:
     * habria que tener en cuenta positivizar la imagen, esta expresion??
     */
    CImg<double> get_mascara_difusa( CImg<double> mask, int factor=1 ) { 
        CImg<double> img = *this;
        return factor*img - img.get_convolve( mask );
    }
    /**
     * Realiza un filtrado de alta potencia - HighBoost
     * g(x,y) = (A-1)*f(x,y) + PA{ f(x,y) }   donde factor = A 
     * Si factor=1 =>  g(x,y) = PA{ f(x,y) }  pasa altos normal
     * Si factor>1 =>  g(x,y) = k*f(x,y) + PA{ f(x,y) } agrega parte baja frec
     * @mask mascara pasa altos
     * @factor facator  A aplicado a la imagen
     * FIXME:
     * Podria calcularse mediante mascara difusa (formula con pasa bajos)
     * g(x,y) = (A*f(x,y) - PB{ f(x,y) }
     * pero habria que tener en cuenta positivizar la imagen, esta expresion
     * con (A-1)... es mas util para la implementacion
     */
    CImg<double> get_alta_potencia( CImg<double> mask, int factor=1 ) { 
        CImg<double> img = *this;
        return (factor-1)*img + img.get_convolve( mask );
    }


    /**
     * Equalizacion local: realiza un ecualizado segun tam mask
     */
    CImg<double> get_local_equalize( int dx=3, int dy=3, int nivel_equalize=255 ) {
        CImg<double> img = *this;
        CImg<double> mask(3,3),
            dest( img );
        int midx=(dx/2), midy=(dy/2), z=0, c=0;
        
        for( int i=midx; i<=img.width()-midx; i+=(2*midx) ) {
            for( int j=midy; j<=img.height()-midy; j+=(2*midy) ) {
                mask = img.get_crop( i-midx, j-midy, i+midx, j+midy );

                mask.equalize( nivel_equalize );

                for( int x=-midx; x<=midx; x++){
                    for(int y=-midy; y<=midy; y++){
                        dest( i+x, j+y) = mask( x+midx, y+midy );
                    }
                }
            }
        }
        return dest;
    }

    // ==================================================== \\
    // ----------------------- color  --------------------- \\

    CImg<double> get_aplicar_paleta(int nro_paleta=1){
        CImg<double> img = *this;
        return aplicar_paleta(img,nro_paleta);
    }

    // ==================================================== \\
    // --------------- espectro frecuencia  ---------------- \\

    CImg<double> get_a_solo_fase( ) {
        CImg<double> img = *this;
        return a_solo_fase( img );
    }

    CImg<double> get_a_solo_modulo( ) {
        CImg<double> img = *this;
        return a_solo_modulo( img );
    }

    CImg<double> get_a_solo_modulo_log( ) {
        CImg<double> img = *this;
        return a_solo_modulo_log( img );
    }

    CImg<double> get_fft_fase( ) {
        CImg<double> img = *this;
        return fft_fase( img );
    }

    CImg<double> get_fft_modulo( bool centrada=true ) {
        CImg<double> img = *this;
        return fft_modulo( img, centrada );
    }

    CImg<double> get_fft_modulo_log( bool centrada=true ) {
        CImg<double> img = *this;
        return fft_modulo_log( img, centrada );
    }

    CImg<double> get_a_fase_definida( CImg<double> fase ) {
        CImg<double> img = *this;
        return a_fase_definida( img, fase );
    }

    CImg<double> get_filtrada( CImg<double> filtro ) {
        CImg<double> img = *this;
        return filtrar( img, filtro );
    }
    /*ojo no se si anda bien!!*/
    CImg<double> get_filtrada_complejo( CImgList<double> filtro ) {
        CImg<double> img = *this;
        return filtrar_complejo( img, filtro );
    }

    // ==================================================== \\
    // --------------- Filtrado Alta Potencia --------------- \\

    CImg<double> get_filtrado_alta_potencia( CImg<double> filtro, double a=1 ) {
        CImg<double> img = *this;
        return filtrado_alta_potencia( img, filtro, a );
    }

    // ==================================================== \\
    // --------------- Filtrado Homomorfico --------------- \\

    CImg<double> get_filtrado_homomorfico( CImg<double> filtro ) {
        CImg<double> img = *this;
        return filtrado_homomorfico( img, filtro );
    }

    // ==================================================== \\
    // --------------- Generacionde ruido  --------------- \\

    CImg<double> ruido_gaussiano( double sigma ) {
        gen_ruido_gaussiano( *this, sigma );
        return *this;
    }

    CImg<double> get_ruido_gaussiano( double sigma ) {
        CImg<double> img = *this;
        gen_ruido_gaussiano( img, sigma );
        return img;
    }

    CImg<double> ruido_uniforme( double sigma ) {
        gen_ruido_uniforme( *this, sigma );
        return *this;
    }

    CImg<double> get_ruido_uniforme( double sigma ) {
        CImg<double> img = *this;
        gen_ruido_uniforme( img, sigma );
        return img;
    }

    CImg<double> ruido_sal_y_pimienta( double sigma ) {
        gen_ruido_sal_y_pimienta( *this, sigma );
        return *this;
    }

    CImg<double> get_ruido_sal_y_pimienta( double sigma ) {
        CImg<double> img = *this;
        gen_ruido_sal_y_pimienta( img, sigma );
        return img;
    }

    CImg<double> ruido_sal( double sigma ) {
        gen_ruido_sal( *this, sigma );
        return *this;
    }

    CImg<double> get_ruido_sal( double sigma ) {
        CImg<double> img = *this;
        gen_ruido_sal( img, sigma );
        return img;
    }

    CImg<double> ruido_pimienta( double sigma ) {
        gen_ruido_pimienta( *this, sigma );
        return *this;
    }

    CImg<double> get_ruido_pimienta( double sigma ) {
        CImg<double> img = *this;
        gen_ruido_pimienta( img, sigma );
        return img;
    }

    // ==================================================== \\
    // ------ filtrado espacial tema:restauracion  -------- \\

    // ----- filtros de medias
    
    CImg<double> get_filtrar_aritmetica( int size=3 ) {
        return filtrado_aritmetica( *this, size );
    }

    CImg<double> filtrar_aritmetica( int size=3 ) {
        *this = filtrado_aritmetica( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_geometrica( int size=3 ) {
        return filtrado_geometrica( *this, size );
    }

    CImg<double> filtrar_geometrica( int size=3 ) {
        *this = filtrado_geometrica( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_armonica( int size=3 ) {
        return filtrado_armonica( *this, size );
    }

    CImg<double> filtrar_armonica( int size=3 ) {
        *this = filtrado_armonica( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_contra_armonica( int q=0, int size=3 ) {
        return filtrado_contra_armonica( *this, size );
    }

    CImg<double> filtrar_contra_armonica( int q=0, int size=3 ) {
        *this = filtrado_contra_armonica( *this, size );
        return *this;
    }

    // ----- filtros de orden

    CImg<double> filtrar_mediana( int size=3 ) {
        *this =  filtrado_mediana( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_mediana( int size=3 ) {
        return filtrado_mediana( *this, size );
    }

    CImg<double> filtrar_max( int size=3 ) {
        *this =  filtrado_max( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_max( int size=3 ) {
        return filtrado_max( *this, size );
    }

    CImg<double> filtrar_min( int size=3 ) {
        *this =  filtrado_min( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_min( int size=3 ) {
        return filtrado_min( *this, size );
    }

    CImg<double> filtrar_punto_medio( int size=3 ) {
        *this =  filtrado_punto_medio( *this, size );
        return *this;
    }

    CImg<double> get_filtrar_punto_medio( int size=3 ) {
        return filtrado_punto_medio( *this, size );
    }

    CImg<double> get_filtrar_alfa_recortado( double d=0, int size=3 ) {
        return filtrado_alfa_recortado( *this, d, size );
    }

    // ====================================================== \\
    // - filtrado espacial con convolucion tema:segmentacion - \\

    CImg<double> get_filtrar_roberts() {
        return filtrado_roberts( *this );
    }

    CImg<double> filtrar_roberts() {
        *this = filtrado_roberts( *this );
        return *this;
    }

    CImg<double> get_filtrar_prewitt() {
        return filtrado_prewitt( *this );
    }

    CImg<double> filtrar_prewitt() {
        *this = filtrado_prewitt( *this );
        return *this;
    }

    CImg<double> get_filtrar_sobel() {
        return filtrado_sobel( *this );
    }

    CImg<double> filtrar_sobel() {
        *this = filtrado_sobel( *this );
        return *this;
    }

    CImg<double> get_filtrar_laplaciano_g() {
        return filtrado_laplaciano_g( *this );
    }

    CImg<double> filtrar_laplaciano_g() {
        *this = filtrado_laplaciano_g( *this );
        return *this;
    }


};
