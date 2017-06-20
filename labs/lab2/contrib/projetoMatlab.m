%% Aguarda conexão com Arduino e a configura

% Variáveis da Workspace
clear all;
clc;

% Escolha de qual filtro plotar (soma plota mais de um dos filtros)
% 1 = Kalman
% 2 = media
% 4 = mediaMovel_20
% 8 = mediaMovel_100
% 16 = mediaMovelPonderada_09
% 32 = mediaMovelPonderada_07
% 64 = mediaMovelPonderada_05
filtro = 127; % Plota todos os filtros

cont = 0;

lm35 = 0;       % Temperatura da ponta fria
termopar = 0;   % Temperatura da ponta quente

media = 0;

mediaMovel_20 = 0;
mediaMovel_100 = 0;

mediaMovelPonderada_09 = 0;
mediaMovelPonderada_07 = 0;
mediaMovelPonderada_05 = 0;

mediaKalman = 0;

% Aguarda conexão com Arduino
serialInfo = instrhwinfo('serial');
while(size(serialInfo.AvailableSerialPorts) == [0 1])
    serialInfo = instrhwinfo('serial');
end

% Define a porta
s1 = serial(serialInfo.AvailableSerialPorts{1});
clear serialInfo;

% Configura Handler
s1.BytesAvailableFcnMode = 'terminator';
% s1.BytesAvailableFcnCount = numero de bytes;
% s1.BytesAvailableFcnMode = 'byte';
s1.BytesAvailableFcn = @(s1,event)meuCallBack(s1,event);

% Abre conexão
fopen(s1);

%% Muda valor do filtro
% 1 = Kalman
% 2 = media
% 4 = mediaMovel_20
% 8 = mediaMovel_100
% 16 = mediaMovelPonderada_09
% 32 = mediaMovelPonderada_07
% 64 = mediaMovelPonderada_05
filtro = 127;

%% Somente Pausa Arduino
fprintf(s1,'PAUSE');

%% Pausa e reseta variáveis (do Matlab e do Arduino)
fprintf(s1,'PAUSE_RESET');
cont = 0;
lm35 = 0;
termopar = 0;
media = 0;
mediaMovel_20 = 0;
mediaMovel_100 = 0;
mediaMovelPonderada_09 = 0;
mediaMovelPonderada_07 = 0;
mediaMovelPonderada_05 = 0;
mediaKalman = 0;

%% Retoma Arduíno
fprintf(s1,'START');

%% Desconecta o Arduíno
fclose(s1);
delete(s1);
clear s1;
