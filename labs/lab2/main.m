function main()
% Função principal do MATLAB

% Abrir o Arduino
arduino = serial(input('What port? ', 's'), 'BaudRate', 9600);
fopen(arduino);
stuff = [ ];

% Ler os valores
for i = 1:1000
    line = fgetl(arduino);
    fprintf('%s\n', line);
end

% Fechar o Arduino
fclose(arduino);
