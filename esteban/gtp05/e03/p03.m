wc = 10
H  = zeros(50,50);
n  = 10;

for i=1:50
  for j=1:50
    d = sqrt( (i-25)^2 + (j-25)^2 );
    H(i,j) = 1 / ( 1 + (d/wc)^(2*n) );
  endfor
endfor

figure
mesh([1:50],[1:50],H)
title("frec H")

figure
mesh([1:50],[1:50],fftshift(abs(ifft2(H))))
title ("tiempo h")
