function main()
% Esta é a função que deverá ser chamada realizar as tarefas.
%

close all;
% Gerando dados de entrada
[tempo altitude] = gerarEntrada();
limite = length(tempo);
disp('Exercício 1');
mediaAtual = [ ];
for n = 1:limite
    mediaAtual(end+1) = media1(altitude(n));
end
handle = figure;
hold on;
% TODO Colocar legendas
plot(tempo, altitude, 'r');
plot(tempo, mediaAtual, 'b');
hold off;
saveas(handle, 'mediaregular.jpg');
disp('Exercício 2');
mediaAtual = [ ];
for n = 1:limite
    mediaAtual(end+1) = media2(altitude(n));
end
handle = figure;
hold on;
plot(tempo, altitude, 'r');
plot(tempo, mediaAtual, 'b');
hold off;
saveas(handle, 'mediamovel.jpg');
disp('Exercício 3');
mediaAtual = [ ];
for n = 1:limite
    mediaAtual(end+1) = media3(altitude(n));
end
handle = figure;
hold on;
plot(tempo, altitude, 'r');
plot(tempo, mediaAtual, 'b');
hold off;
saveas(handle, 'mediaponderada.jpg');
