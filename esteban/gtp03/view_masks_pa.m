nx = 3
ny = 3

# ############### filtros PA: acentuadores ##############

# =============== suma uno bajo =================
#  0  -1   0
# -1   5  -1 
#  0  -1   0
suma_uno_bajo = ones(nx,ny).*(-1);
suma_uno_bajo(1,1)=0;
suma_uno_bajo(3,1)=0;
suma_uno_bajo(1,3)=0;
suma_uno_bajo(3,3)=0;
suma_uno_bajo(2,2)=5;
suma_uno_bajo
figure
mesh( [1:nx], [1:ny], suma_uno_bajo );
title("mascara suma uno bajo")


# =============== suma uno medio =================
#  1  -2   1
# -2   5  -2 
#  1  -2   1
suma_uno_medio = ones(nx,ny).*(-2);
suma_uno_medio(1,1)=1;
suma_uno_medio(3,1)=1;
suma_uno_medio(1,3)=1;
suma_uno_medio(3,3)=1;
suma_uno_medio(2,2)=5;
suma_uno_medio
figure
mesh( [1:nx], [1:ny], suma_uno_medio );
title("mascara suma uno medio")

# =============== suma uno alto =================
# -1  -1  -1
# -1   9  -1 
# -1  -1  -1

suma_uno_alto = ones(nx,ny).*(-1);
suma_uno_alto(2,2)=9;
suma_uno_alto
figure
mesh( [1:nx], [1:ny], suma_uno_alto );
title("mascara suma uno medio")
