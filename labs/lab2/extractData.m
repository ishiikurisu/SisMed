function [t m1 m2] = extractData(raw)
% Process a line generated by the Arduino.
%
% Input:
%
%    raw: the raw line, as read from Arduino serial
%
% Output:
%
%     t: time
%     m1: first table value
%     m2: second table value
%
stuff = split_string(raw, ';');
t = str2num(stuff{1});
m1 = str2num(stuff{2});
m2 = str2num(stuff{3});

function [outlet] = split_string(inlet, delim)
% Splits a string into a delimiter string.
%
%     [outlet] = split_string(inlet, delim);
%
% Creats a cell array `outlet` with the separated strings from `inlet` by
% `delim`.
% Taken from https://github.com/lab-neuro-comp/P2/blob/master/P2lib/util/split_string.m
%
outlet = tokenizeString(inlet, delim);

function [tokens] = tokenizeString(string,delimeter)
tokens = {};
while not(isempty(string))
    [tokens{end+1},string] = strtok(string,delimeter);
end
