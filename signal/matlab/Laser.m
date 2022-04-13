close all;
T=0.0002;
M=64;
Te=T/M; %Fe = 320kH
Tsim=T-Te;
A1 = 1;
A2 = 0;
A3 = 0;
A4 = 0;
A5 = 0;
A6 = 0;
F1 = 85000;
F2 = 90000;
F3 = 95000;
F4 = 100000;
F5 = 115000;
F6 = 120000;
Res=sim('LaserSim');
plot(Res.Signal_Continu);
hold on;
plot(Res.Signal_Echanti, 'o');
x=linspace(0,M-1,M)/T;
data = Res.Signal_Echanti.data;
%for i = 1:32
 %   data(i) = 0;
%end
fourier = fft(data,M);
f = (abs(fourier) / M);
figure;
plot(x,f,'o');
TF= tf([1],[1.7483e-23, 7.6663e-18, 1.162e-11, 3.0332e-6, 1]);
figure;
bode(TF);
