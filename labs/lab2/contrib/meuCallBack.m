function [serial , event] = meuCallBack( serial , event )
%MEUCALLBACK Ação tomada a um evento da porta
%   Lê entrada e plota
    
    % Lê dados de entrada do serial e colocá-os em um vetor de double
    valor = fscanf(serial);
    valor = strsplit(valor,',');
    valor = str2double(valor);
    
    % Carrega dados da Workspace
    cont = evalin('base','cont') + 1;
    lm35 = evalin('base','lm35');
    termopar = evalin('base','termopar');
    media = evalin('base','media');
    mediaMovel_20 = evalin('base','mediaMovel_20');
    mediaMovel_100 = evalin('base','mediaMovel_100');
    mediaMovelPonderada_09 = evalin('base','mediaMovelPonderada_09');
    mediaMovelPonderada_07 = evalin('base','mediaMovelPonderada_07');
    mediaMovelPonderada_05 = evalin('base','mediaMovelPonderada_05');
    mediaKalman = evalin('base','mediaKalman');
    
    % Adicina os dados lidos
    lm35(cont) = valor(1);
    termopar(cont) = valor(2);
    media(cont) = valor(3);
    mediaMovel_20(cont) = valor(4);
    mediaMovel_100(cont) = valor(5);
    mediaMovelPonderada_09(cont) = valor(6);
    mediaMovelPonderada_07(cont) = valor(7);
    mediaMovelPonderada_05(cont) = valor(8);
    mediaKalman(cont) = valor(9);
    
    % Salva na Workspace
    assignin('base','cont',cont);
    assignin('base','lm35',lm35);
    assignin('base','termopar',termopar);
    assignin('base','media',media);
    assignin('base','mediaMovel_20',mediaMovel_20);
    assignin('base','mediaMovel_100',mediaMovel_100);
    assignin('base','mediaMovelPonderada_09',mediaMovelPonderada_09);
    assignin('base','mediaMovelPonderada_07',mediaMovelPonderada_07);
    assignin('base','mediaMovelPonderada_05',mediaMovelPonderada_05);
    assignin('base','mediaKalman',mediaKalman);
    
    % Plota a cada segundo
    if(mod(cont,20) == 0)
        % Configura escala de tempo
        if(cont-399 > 0)
            cont2 = (cont-400-mod(cont*0.05,10)*20+1):cont;
        else
            cont2 = 1:cont;
        end
        tempo = cont2*0.05;
        
        % Plota temperatura da ponta quente
        figure(1);
        plot(tempo,termopar(cont2));
        
        % Plota uma dos resultados dos filtros
        filtro =  evalin('base','filtro');
        filtro = dec2bin(filtro);
        for i = 1:(7-length(filtro))
            filtro = strcat('0',filtro);
        end
        
        figure(2);
        plot(tempo,termopar(cont2));
        hold on;
%         if(filtro(7) == '1')
            plot(tempo,mediaKalman(cont2));
            hold on;
%         end
%         if(filtro(6) == '1')
            plot(tempo,media(cont2));
            hold on;
%         end
%         if(filtro(5) == '1')
%             plot(tempo,mediaMovel_20(cont2));
%             hold on;
%         end
%         if(filtro(4) == '1')
%             plot(tempo,mediaMovel_100(cont2));
%             hold on;
%         end
%         if(filtro(3) == '1')
%             plot(tempo,mediaMovelPonderada_09(cont2));
%             hold on;
%         end
%         if(filtro(2) == '1')
%             plot(tempo,mediaMovelPonderada_07(cont2));
%             hold on;
%         end
%         if(filtro(1) == '1')
%             plot(tempo,mediaMovelPonderada_05(cont2));
%         end
        hold off;
        legend('Medição','Kalman','media');
        
        clc;
        display(strcat('Ponta fria = ', num2str(lm35(cont))));
        display(strcat('Ponta quente = ', num2str(termopar(cont))));
        display(strcat('Kalman = ', num2str(mediaKalman(cont))));
        display(strcat('Média = ', num2str(media(cont))));
        display(strcat('Média Móvel (n = 20) = ', num2str(mediaMovel_20(cont))));
        display(strcat('Média Móvel (n = 100) = ', num2str(mediaMovel_100(cont))));
        display(strcat('Média Móvel Ponderada(a = 0.9) = ', num2str(mediaMovelPonderada_09(cont))));
        display(strcat('Média Móvel Ponderada(a = 0.7) = ', num2str(mediaMovelPonderada_07(cont))));
        display(strcat('Média Móvel Ponderada(a = 0.5) = ', num2str(mediaMovelPonderada_05(cont))));
    end
end

