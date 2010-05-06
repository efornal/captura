h = zeros(25,25);
h(11:15,11:15) = 1;
H=fft(h);
mesh([1:25],[1:25],fftshift(abs(H)))
