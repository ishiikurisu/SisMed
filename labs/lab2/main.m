function main()
% Função principal do MATLAB
%

% Preparando os dados
inlet = [ ];
meanFiltered = [ ];
windowedFiltered = [ ];
expFiltered = [ ];

% Abrir o Arduino
howMany = input('Quantas medidas? ');
arduino = serial(input('Qual porta? ', 's'), 'BaudRate', 9600);
fopen(arduino);

% Ler os valores
for n = 1:howMany
    line = fgetl(arduino);
    [t mm mw me] = extractData(line);
    inlet(end+1) = t;
    meanFiltered(end+1) = mm;
    windowedFiltered(end+1) = mw;
    expFiltered(end+1) = me;
end

% Desenhando os gráficos
figure; plot(inlet, meanFiltered);
figure; plot(inlet, windowedFiltered);
figure; plot(inlet, expFiltered);

% Fechar o Arduino
fclose(arduino);
