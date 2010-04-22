nx = 3
ny = 3

# =============== impulso =================
#  0 0 0
#  0 1 0
#  0 0 0
impulso = zeros(nx,ny);
impulso(2,2)=1;
impulso
figure
mesh( [1:nx], [1:ny], impulso );
title("mascara impulso")


# ############### filtros PB: promediadores ##############

# =============== media estandar =================
#  1 1 1
#  1 1 1 * 1/9
#  1 1 1
media_estandar = ones(nx,ny).* 1/9;
media_estandar
figure
mesh( [1:nx], [1:ny], media_estandar );
title("mascara media Estandar")


# =============== signo mas =================
#  0 1 0
#  1 1 1 * 1/5
#  0 1 0
signo_mas = ones(nx,ny);
signo_mas(1,1)=0;
signo_mas(3,1)=0;
signo_mas(1,3)=0;
signo_mas(3,3)=0;
signo_mas.* 1/5;
signo_mas
figure
mesh( [1:nx], [1:ny], signo_mas );
title("mascara signo mas")

# =============== ponderada =================
#  1 2 1
#  2 4 2 * 1/16
#  1 2 1
ponderada = ones(nx,ny)*2;
ponderada(1,1)=1;
ponderada(3,1)=1;
ponderada(1,3)=1;
ponderada(3,3)=1;
ponderada.* 1/16;
ponderada
figure
mesh( [1:nx], [1:ny], ponderada );
title("mascara ponderada")
# =============== promedio =================

#  1 1 . 1
#  1 1 . 1 #* 1/N^2   (N = m*n)
#  . . . 1
#  1 1 1 1
promedio = ones(nx,ny);
promedio.* 1/9;
promedio
figure
mesh( [1:nx], [1:ny], promedio );
title("mascara promedio")

# =============== gauseana =================

# for x=fix(nx/2):nx+fix(nx/2)-1
#   for y=fix(ny/2):ny+fix(ny/2)-1
#     #g(x,y) = exp( -((x-1)^2 + y^2)/(2*var^2) );
#     g(x-1,y-1)=0;
#   endfor
# endfor
gaussiana = ones(nx,ny);
c = 1/sqrt(2*pi);
var = 1;

gaussiana(1,1) =  exp( -((-1)^2 + (-1)^2)/(2*var^2) );
gaussiana(2,1) =  exp( -(0^2 + (-1)^2)/(2*var^2) );
gaussiana(3,1) =  exp( -(1^2 + (-1)^2)/(2*var^2) );

gaussiana(1,2) =  exp( -((-1)^2 + 0^2)/(2*var^2) );
gaussiana(2,2) =  exp( -(0^2 + 0^2)/(2*var^2) );
gaussiana(3,2) =  exp( -(1^2 + 0^2)/(2*var^2) );

gaussiana(1,3) =  exp( -((-1)^2 + 1^2)/(2*var^2) );
gaussiana(2,3) =  exp( -(0^2 + 1^2)/(2*var^2) );
gaussiana(3,3) =  exp( -(1^2 + 1^2)/(2*var^2) );

gaussiana
figure
mesh( [1:nx], [1:ny], gaussiana );
title("mascara gaussiana")
