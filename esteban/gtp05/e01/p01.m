rect = zeros(50,50);
rect(20:30,20:30)=1;

mesh([1:50],[1:50],rect);
title("tiempo h");

rectf = fft2(rect);
figure
mesh([1:50],[1:50],fftshift(abs(rectf)));
title("frecuencia H");

