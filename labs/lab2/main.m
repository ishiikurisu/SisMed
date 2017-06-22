function main()
% Função principal do MATLAB

% Abrir o Arduino
howMany = input('Quantas medidas? ');
arduino = serial(input('Qual porta? ', 's'), 'BaudRate', 9600);
fopen(arduino);

% Ler os valores
for n = 1:howMany
    line = fgetl(arduino);
    disp(line);
end

% Fechar o Arduino
fclose(arduino);

% TODO Implement plot functions
% TODO Pick current filter
