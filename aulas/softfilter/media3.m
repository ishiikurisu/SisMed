function [mediaAtual] = media3(x)
% Calcula a média dos valores dados.
% `x` é o valor atual.
%
persistent m; % média
persistent a; % parâmetro alfa

if isempty(m)
    m = 0;
    a = 0.7;
end

m = a*m + (1-a)*x;
mediaAtual = m;
