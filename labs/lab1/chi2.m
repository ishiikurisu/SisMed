function [x2] = chi2(qi, qo)
% Calculates the CHI^2 parameter for the expected (qi) and obtained (qo) arrays
q = [ ];
limit = length(qi);
for n = 2:limit
     q(n) = ((qi(n)-qo(n))^2) / qi(n);
end
x2 = sum(q);
