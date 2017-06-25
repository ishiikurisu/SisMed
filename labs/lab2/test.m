function test
% Tests the output of the implemented filters
%
T = [ ];
M = [ ];
R = [ ];
fp = fopen(strcat('sensor', filesep, 'out.txt'), 'r');
line = fgetl(fp);
while ischar(line)
    % TODO Process line
    [t m r] = extractData(line);
    T(end+1) = t;
    M(end+1) = m;
    R(end+1) = r;
    line = fgetl(fp);
end
fclose(fp);
figure;
hold on;
plot(T, M, 'b');
plot(T, R, 'r');
hold off;
