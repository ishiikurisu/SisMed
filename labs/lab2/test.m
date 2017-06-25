function test
% Tests the output of the implemented filters
%
fp = fopen(strcat('sensor', filesep, 'out.txt'), 'r');
line = fgetl(fp);
while ischar(line)
    % TODO Process line
    [t m r] = extractData(line);
    plotLine(t, m, r);
    line = fgetl(fp);
end
fclose(fp);
