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

};

