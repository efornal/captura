#include </usr/include/CImg.h>
#ifdef namestace_captura 
#else
#define namestace_captura = cimg_captura;


namespace cimg_captura{

    template<typename T> struct CImg : public cimg_library::CImg<T> {
        
        // Constructores replicados

        explicit CImg( const unsigned int dx=0, 
                       const unsigned int dy=1,
                       const unsigned int dz=1, 
                       const unsigned int dv=1 )
            : CImg<T>(dx,dy,dz,dv){};
        
        explicit CImg( const unsigned int dx, 
                       const unsigned int dy,
                       const unsigned int dz, 
                       const unsigned int dv, const T& val )
            : cimg_library::CImg<T>(dx,dy,dz,dv,val) {};

        template<typename t> CImg( const CImg<t>& img )
            : CImg<T>(img) {}

    CImg( const CImg<T>& img )
        : cimg_library::CImg<T>(img) {}
    
        template<typename t> CImg( const CImg<t>& img,
                                   const bool pixel_copy )
            : CImg<T>(img,pixel_copy) {}
    
    CImg( const char *const filename )
        : cimg_library::CImg<T>( filename ) {}

        template<typename t> CImg( const t *const data_buffer,
                                   const unsigned int dx, 
                                   const unsigned int dy=1,
                                   const unsigned int dz=1,
                                   const unsigned int dv=1,
                                   const bool multiplexed=false )
            : CImg<T>( data_buffer, dx, dy, dz, dv, multiplexed) {}

    // ================== nueva funcionalidad ================== \\


    //! Operator<().
        CImg<T> operator<(const CImg<unsigned char> img) const {
            cimg_forXY( this, x, y ) {
                this(x,y) = ( this(x,y) < img(x,y) ) ? 0 : 255;
            }
        }
     /*
     CImg<unsigned char> menor ( CImg<unsigned char>img2 ) {
         cimg_forXY( *this, x, y ) {
             this(x,y) = ( this(x,y) < img2(x,y) ) ? 0 : 255;
         }
         return *this;
     }
     */

    }; //fin struct
};

#endif
