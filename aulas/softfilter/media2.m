function [mediaAtual] = media2(a)
% Calcula a média móvel dos valores dados.
% `a` é o valor atual.
%
persistent m; % média
persistent n; % tamanho da janela
persistent q; % fila de dados

if isempty(q)
    m = 0;
    n = 100;
    q = java.util.LinkedList;
end

q.add(a);
if q.size < n
    m = media1(a);
else
    m = m + (a - q.pop())/n;
end

mediaAtual = m;
