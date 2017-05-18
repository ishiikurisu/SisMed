function [mediaAtual] = media1(a)
% Calcula a média dos valores dados.
% `a` é o valor atual.
%
persistent k; % número de amostras
persistent m; % média

if isempty(k)
    m = 0;
    k = 0;
end

k = k+1;
m = (k-1)*m/k + a/k;
mediaAtual = m;
