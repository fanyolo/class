clc;
clear;
close all;

%  一、绘制二元熵函数曲线
%  H(p) = -p log2(p) - (1-p) log2(1-p)

p = 0:0.001:1;

H2 = zeros(size(p));

for i = 1:length(p)
    if p(i) == 0 || p(i) == 1
        H2(i) = 0;
    else
        H2(i) = -p(i)*log2(p(i)) - (1-p(i))*log2(1-p(i));
    end
end

figure;
plot(p, H2, 'LineWidth', 2);
grid on;
xlabel('p');
ylabel('H(p)');
title('二元信源熵函数曲线');


%  二、绘制三元熵函数曲面
%  H(p1,p2,p3) = -sum(pi log2 pi)
%  其中 p3 = 1 - p1 - p2

step = 0.01;
p1 = 0:step:1;
p2 = 0:step:1;

[P1, P2] = meshgrid(p1, p2);
P3 = 1 - P1 - P2;

H3 = zeros(size(P1));

for i = 1:size(P1, 1)
    for j = 1:size(P1, 2)
        if P3(i, j) >= 0
            probs = [P1(i, j), P2(i, j), P3(i, j)];
            H_temp = 0;

            for k = 1:3
                if probs(k) > 0
                    H_temp = H_temp - probs(k) * log2(probs(k));
                end
            end

            H3(i, j) = H_temp;
        else
            H3(i, j) = NaN;
        end
    end
end

figure;
surf(P1, P2, H3);
shading interp;
grid on;
xlabel('p_1');
ylabel('p_2');
zlabel('H(p_1,p_2,p_3)');
title('三元信源熵函数曲面');


%  三、统计英文文档中字母与空格概率分布及信源熵

filename = 'source.txt';

fid = fopen(filename, 'r');

if fid == -1
    error('无法打开文件，请确认 source.txt 是否在当前工作目录下。');
end

text = fread(fid, '*char')';
fclose(fid);

% 转换为小写
text = lower(text);

% 统计对象：26 个英文字母 + 空格
symbols = ['a':'z', ' '];
counts = zeros(1, length(symbols));

% 统计频数
for i = 1:length(text)
    ch = text(i);

    for j = 1:length(symbols)
        if ch == symbols(j)
            counts(j) = counts(j) + 1;
            break;
        end
    end
end

% 总符号数
total_count = sum(counts);

if total_count == 0
    error('文档中没有英文字母或空格。');
end

% 计算概率分布
probabilities = counts / total_count;

% 计算信源熵
H_source = 0;

for i = 1:length(probabilities)
    if probabilities(i) > 0
        H_source = H_source - probabilities(i) * log2(probabilities(i));
    end
end

% 输出统计结果

fprintf('\n英文信源文档统计结果\n');
fprintf('总符号数：%d\n\n', total_count);

fprintf('符号\t频数\t 概率\n');
fprintf('-----------------------------\n');

for i = 1:length(symbols)
    if symbols(i) == ' '
        fprintf('空格\t%d\t%.6f\n', counts(i), probabilities(i));
    else
        fprintf('%c\t %d\t %.6f\n', symbols(i), counts(i), probabilities(i));
    end
end

fprintf('\n该信源的熵 H = %.6f bit/symbol\n', H_source);

% 绘制概率分布柱状图

figure;

bar(probabilities);
grid on;

xticks(1:length(symbols));

symbol_labels = cell(1, length(symbols));
for i = 1:length(symbols)
    if symbols(i) == ' '
        symbol_labels{i} = 'space';
    else
        symbol_labels{i} = symbols(i);
    end
end

xticklabels(symbol_labels);

xlabel('符号');
ylabel('概率');
title('英文信源中字母与空格的概率分布');