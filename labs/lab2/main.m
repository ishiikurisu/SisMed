function main()
% Função principal do MATLAB

% Abrir o Arduino
arduino = serial(input('Qual porta? ', 's'), 'BaudRate', 9600);
fopen(arduino);
stuff = [ ];

% Ler os valores
userInput = input('Qual filtro e quantas medidas? ', 's');
[filterKind howMany] = sscanf(userInput, '%s %f');
fprintf(arduino, '%s\n', userInput);
line = fgetl(arduino);
fprintf('%s\n', line);

% Fechar o Arduino
fclose(arduino);

% TODO Implement plot functions
% TODO Pick current filter
