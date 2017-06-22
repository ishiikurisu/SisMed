function main()
% Função principal do MATLAB
%

% Preparando os dados
inlet = [ ];
lm35 = [ ];
thermocouple = [ ];

% Abrir o Arduino
howMany = input('Quantas medidas? ');
arduino = serial(input('Qual porta? ', 's'), 'BaudRate', 9600);
fopen(arduino);

% Ler os valores
for n = 1:howMany
    line = fgetl(arduino);
    [t m1 m2] = extractData(line);
    inlet(end+1) = t;
    lm35(end+1) = m1;
    thermocouple(end+1) = m2;
end

% Desenhando os gráficos
figure; plot(inlet, lm35);
figure; plot(inlet, thermocouple);

% Fechar o Arduino
fclose(arduino);
