function main()
% Performs the study needed in the report

fprintf('--- Loading data\n');
delete stats.csv
delete chis.csv
data = java.util.HashMap;
dirData = dir('*.csv');
dirIndex = [ dirData.isdir ];
CSVs = { dirData(~dirIndex).name };
for n = 1:length(CSVs)
    csv = CSVs{n};
    put(data, csv, loadColumns(csv));
end

fprintf('# QUESTION 1\n');
fp = fopen('stats.csv', 'w');
fprintf(fp, 'File\tExpected\tObtained\n')
for n = 1:length(CSVs)
    csv = CSVs{n};
    matrix = get(data, csv);
    qi = matrix(:,1);
    qo = matrix(:,2);
    fprintf(fp, '%s\t%.6f +- %.6f\t%.6f +- %.6f\n', csv, mean(qi), std(qi), mean(qo), std(qo));
end
fclose(fp);
fprintf('Check stats.csv\n');

fprintf('# QUESTION 2\n');
% Condensing files into two arrays
expected = [];
obtained = [];
for n = 1:length(CSVs)
    csv = CSVs{n};
    matrix = get(data, csv);
    expected = [ expected; matrix(:,1) ];
    obtained = [ obtained; matrix(:,2) ];
end
% Performing calculations
[m, c] = calib(expected, obtained);
fprintf('Y = %.6f*X + %.6f\n', m, c); % These numbers don't make sense

fprintf('# QUESTION 3\n');
qi = expected;
qo = obtained;
N = length(qi);
sqo = sum((m*qi + c - qo).^2)/N;
sm = sqrt((N*(sqo.^2)) / (N*sum(qi.^2) - sum(qi)^2));
so = sqrt(((sqo^2) * sum(qi.^2)) / (N*sum(qi.^2) - sum(qi)^2));
fprintf('Sqo = %.6f\n', sqo);
fprintf('Sm = %.6f\n', sm);
fprintf('So = %.6f\n', so);

% TODO Complete question 4
% TODO Complete question 5
% TODO Complete question 6

fprintf('# QUESTION 7\n');
fp = fopen('chis.csv', 'w');
fprintf(fp, 'File\tX2\n');
for n = 1:length(CSVs)
    csv = CSVs{n};
    matrix = get(data, csv);
    expected = matrix(:,1);
    obtained = matrix(:,2);
    fprintf(fp, '%s\t%.6f\n', csv, chi2(expected, obtained));
end
fclose(fp);
fprintf('Check chis.csv file\n');

% TODO Complete question 9
