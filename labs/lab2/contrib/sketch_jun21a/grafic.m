% se houver problema com abertura de COM usar o comando 
%    >> delete (instrfindall);

clear all
close all
clc

arduino = serial('COM5','Baudrate',9600,'Parity','none','StopBits',1,'DataBits',8, 'Terminator', 'LF');
pontos = 400; %numero de dados coletados;
fopen(arduino);

i=1;
k = 1:1:pontos;

val=zeros(1,pontos);           %valor real
filtro=zeros(1,pontos);        %valor filtrado

figure;
axis([0 pontos 0 120])
xlabel('time');
ylabel('input');
grid on
hold on

while i<pontos
    
val(1,i) = fscanf(arduino,'%f');
filtro(1,i) = fscanf(arduino,'%f');

plot(k(i),val(1,i),'ko-');
drawnow;
plot(k(i),filtro(1,i),'r*-');
drawnow;

i=i+1;

end

fclose(arduino);
delete(arduino);
clear arduino