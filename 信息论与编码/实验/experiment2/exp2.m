clc;
clear;
close all;

% 实验二：二进制香农编码

% 信源符号
symbols = {'a1','a2','a3','a4','a5','a6','a7'};

% 信源概率
P = [0.2 0.19 0.18 0.17 0.15 0.1 0.01];

% 按概率从大到小排序
[P_sort, index] = sort(P, 'descend');
symbols_sort = symbols(index);

n = length(P_sort);

% 计算码长 li = ceil(-log2(pi))
L = ceil(-log2(P_sort));

% 计算累加概率 Fi
F = zeros(1, n);
for i = 2:n
    F(i) = F(i-1) + P_sort(i-1);
end

% 生成香农编码
codes = cell(1, n);

for i = 1:n
    temp = F(i);
    code = '';

    for j = 1:L(i)
        temp = temp * 2;

        if temp >= 1
            code = [code '1'];
            temp = temp - 1;
        else
            code = [code '0'];
        end
    end

    codes{i} = code;
end

% 计算信源熵
H = 0;
for i = 1:n
    H = H - P_sort(i) * log2(P_sort(i));
end

% 计算平均码长
L_avg = sum(P_sort .* L);

% 计算编码效率
eta = H / L_avg;

% 输出结果

fprintf('二进制香农编码结果\n\n');

fprintf('%-7s %-8s %-9s %-7s %-10s\n', ...
    '符号', '概率', '累加概率', '码长', '码字');
fprintf('------------------------------------------------------\n');

for i = 1:n
    fprintf('%-8s %-10.2f %-12.2f %-8d %-10s\n', ...
        symbols_sort{i}, P_sort(i), F(i), L(i), codes{i});
end

fprintf('\n信源熵 H(X)    = %.6f bit/symbol\n', H);
fprintf('平均码长 L     = %.6f bit/symbol\n', L_avg);
fprintf('编码效率 η     = %.2f%%\n', eta * 100);