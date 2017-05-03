function [m, c] = calib(qi, qo)
% Calculates the calibration curve parameters based on the expected (qi) and
% obtained (qo) parameters
n = length(qi);
m = (n*sum(qi.*qo) - sum(qi)*sum(qo)) / (n*sum(qi.^2) - sum(qi)^2);
c = (sum(qi.^2)*sum(qo) - sum(qi)*sum(qi.*qo)) / (n*sum(qi.^2) - sum(qi)^2);
