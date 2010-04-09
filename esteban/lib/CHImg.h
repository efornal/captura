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



};

