nx=3
ny=3
g = ones(nx,ny)
c = 1/sqrt(2*pi)
var = .5
# for x=fix(nx/2):nx+fix(nx/2)-1
#   for y=fix(ny/2):ny+fix(ny/2)-1
#     #g(x,y) = exp( -((x-1)^2 + y^2)/(2*var^2) );
#     g(x-1,y-1)=0;
#   endfor
# endfor

g(1,1) =  exp( -((-1)^2 + (-1)^2)/(2*var^2) );
g(2,1) =  exp( -(0^2 + (-1)^2)/(2*var^2) );
g(3,1) =  exp( -(1^2 + (-1)^2)/(2*var^2) );

g(1,2) =  exp( -((-1)^2 + 0^2)/(2*var^2) );
g(2,2) =  exp( -(0^2 + 0^2)/(2*var^2) );
g(3,2) =  exp( -(1^2 + 0^2)/(2*var^2) );

g(1,3) =  exp( -((-1)^2 + 1^2)/(2*var^2) );
g(2,3) =  exp( -(0^2 + 1^2)/(2*var^2) );
g(3,3) =  exp( -(1^2 + 1^2)/(2*var^2) );

g
mesh([1:nx],[1:ny],g);

