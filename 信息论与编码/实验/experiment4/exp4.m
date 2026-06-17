clc;
clear;
close all;

% 实验四：一般离散信道容量迭代算法

% 输入信道参数

m = input('请输入信源符号个数 m：');
n = input('请输入信宿符号个数 n：');

if m <= 0 || n <= 0 || floor(m) ~= m || floor(n) ~= n
    error('信源符号个数和信宿符号个数必须为正整数。');
end

P = zeros(m, n);

fprintf('\n请输入信道转移概率矩阵 P(y|x)：\n');
fprintf('每一行表示一个输入符号到各输出符号的转移概率\n');
fprintf('例如：[0.7 0.3]\n\n');

for i = 1:m
    row = input(sprintf('请输入第 %d 行的 %d 个转移概率：', i, n));

    if length(row) ~= n
        error('第 %d 行输入的概率个数不等于 %d。', i, n);
    end

    P(i, :) = row;
end

% 检查转移概率矩阵是否合法

if any(P(:) < 0) || any(P(:) > 1)
    error('转移概率必须在 0 到 1 之间。');
end

for i = 1:m
    row_sum = sum(P(i, :));
    if abs(row_sum - 1) > 1e-6
        error('第 %d 行概率之和不等于 1，请检查输入。', i);
    end
end

% 初始化参数

% 初始信源分布，采用均匀分布
p = ones(1, m) / m;

% 最大迭代次数
max_iter = 10000;

% 收敛精度
epsilon = 1e-10;

% 记录容量变化
C_old = 0;
C_record = zeros(1, max_iter);

% 迭代计算信道容量

for iter = 1:max_iter

    % 计算输出分布 q(y)
    q = p * P;

    % 计算 D_i
    D = zeros(1, m);

    for i = 1:m
        for j = 1:n
            if P(i, j) > 0 && q(j) > 0
                D(i) = D(i) + P(i, j) * log2(P(i, j) / q(j));
            end
        end
    end

    % 更新信源分布
    temp = p .* (2 .^ D);
    p_new = temp / sum(temp);

    % 计算新的输出分布
    q_new = p_new * P;

    % 计算当前互信息
    C_new = 0;

    for i = 1:m
        for j = 1:n
            if P(i, j) > 0 && q_new(j) > 0
                C_new = C_new + p_new(i) * P(i, j) * ...
                    log2(P(i, j) / q_new(j));
            end
        end
    end

    % 记录每次迭代的容量
    C_record(iter) = C_new;

    % 判断是否收敛
    if abs(C_new - C_old) < epsilon && max(abs(p_new - p)) < epsilon
        break;
    end

    % 更新变量
    p = p_new;
    C_old = C_new;
end

if iter == max_iter
    warning('达到最大迭代次数，结果可能尚未完全收敛。');
end

% 输出结果

fprintf('\n迭代计算结果\n\n');

fprintf('信道转移概率矩阵 P(y|x)：\n');
disp(P);

fprintf('迭代次数：%d\n\n', iter);

fprintf('最佳信源分布：\n');
for i = 1:m
    fprintf('P(x%d) = %.10f\n', i, p_new(i));
end

fprintf('\n对应输出分布：\n');
for j = 1:n
    fprintf('P(y%d) = %.10f\n', j, q_new(j));
end

fprintf('\n信道容量 C = %.10f bit/symbol\n', C_new);

% 绘制信道容量收敛曲线

figure;
plot(1:iter, C_record(1:iter), 'LineWidth', 2);
grid on;
xlabel('迭代次数');
ylabel('信道容量近似值 C');
title('信道容量迭代收敛曲线');