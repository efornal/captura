wc = 10
H  = ones(50,50);
n  = 10;
d0 = 0.0000001; # para evitar division por cero!
a  = 0.1; # si es > 0 agrega brillo medio !
          # pero no lo agrego porque deberia aumentar
          # solo los valores de la banda de paso, y eso ¿como?

for i=1:50
  for j=1:50
    d = sqrt( (i-25)^2 + (j-25)^2 );
    H(i,j) = 1 / ( 1 + (wc/(d+d0))^(2*n) );
  endfor
endfor

figure
mesh([1:50],[1:50],H)
title("frec H")

figure
mesh([1:50],[1:50],fftshift(abs(ifft2(H))))
title ("tiempo h")
