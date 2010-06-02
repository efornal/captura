H = zeros(25,25);
H(11:15,11:15) = 1;
h=ifft2(H);

mesh([1:25],[1:25],H)
title("frecuencia H")

figure()
mesh([1:25],[1:25],fftshift(abs(h)))
title("tiempo h")