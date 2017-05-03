function [outlet] = loadColumns(fileName)
% Loads the given csv table in a matrix
outlet = [ ];
fp = fopen(fileName);
line = fgetl(fp);
y = 1;
while ischar(line)
    items = splitString(line, '\t');
    for x = 1:length(items);
        outlet(y, :) = str2num(replaceString(items{x}, ',', '.'));
    end
    line = fgetl(fp);
    y = y+1;
end
fclose(fp);
