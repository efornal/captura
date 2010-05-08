H = ones(25,25);
H(11:15,11:15) = 0;
h=ifft2(H);

mesh([1:25],[1:25],H)
title("frecuencia H - abarca el cero : elimina brillo medio!!")

figure
mesh([1:25],[1:25],fftshift(abs(h)))
title("tiempo h")