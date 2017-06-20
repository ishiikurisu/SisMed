function plotLine(t, ms, ref)
% Plots stuff
%
figure;
hold on;
plot(t, ms, 'b');
plot(t, ref, 'r')
hold off;
