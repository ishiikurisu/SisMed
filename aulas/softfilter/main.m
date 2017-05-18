function main()
% Esta é a função que deverá ser chamada realizar as tarefas.
%

% Gerando dados de entrada
[tempo altitude] = gerarEntrada();
limite = length(tempo);
disp('Exercício 1');
mediaAtual = [ ];
for n = 1:limite
    mediaAtual(end+1) = media1(altitude(n));
end
figure;
hold on;
% TODO Colocar legendas
plot(tempo, altitude, 'r');
plot(tempo, mediaAtual, 'b');
hold off;
disp('Exercício 2');
mediaAtual = [ ];
for n = 1:limite
    mediaAtual(end+1) = media2(altitude(n));
end
figure;
hold on;
plot(tempo, altitude, 'r');
plot(tempo, mediaAtual, 'b');
hold off;
