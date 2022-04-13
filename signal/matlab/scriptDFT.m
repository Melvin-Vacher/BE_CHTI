close all;
T=0.0002;
M=64;
Te=T/M; %Fe = 320kH
Tsim=T-Te;
Fsin=115000;
Res=sim('SimulDFT');
plot(Res.Sinus_Continu);
hold on;
plot(Res.Sinus_Echanti, 'o');
x=linspace(0,M-1,M)/T;
fourrier = fft(Res.Sinus_Echanti.data,M);
f = abs(fourrier) / M;
figure;
plot(x,f,'o');
% La transformée de Fourrier contient des symétries autour de Fe, la
% fréquence d'échantillonage (phénomène de repliement du spectre). Elle
% contient aussi des translations par Fe. Cela est lié au fait que la
% transformée de -f est la conjuguaison de celle de f.
% Théorème de Shannon : On doit avoir Fe > 2*Fsin
