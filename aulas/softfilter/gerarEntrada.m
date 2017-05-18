function [tempo altitude] = gerarEntrada()
% Gera os dados para serem usados nos filtros. Tempo em segundos e altitude em metros.
%
tempo = 1:5:100;
altitude = [ ];
for t = 1:length(tempo)
    altitude(t) = 11000 + random('norm', 0, 4);
end
