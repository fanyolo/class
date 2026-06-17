clc;
clear;
close all;

% 实验三：二进制和三进制霍夫曼编码

% 信源符号
symbols = {'a1','a2','a3','a4','a5','a6','a7'};

% 信源概率
P = [0.2 0.19 0.18 0.17 0.15 0.1 0.01];

%% 计算二进制霍夫曼编码

[codes2, len2, process2] = huffman_code(symbols, P, 2);

% 信源熵，单位 bit/symbol
H2 = -sum(P .* log2(P));

% 二进制平均码长，单位 bit/symbol
L_avg2 = sum(P .* len2);

% 二进制编码效率
eta2 = H2 / L_avg2;

%% 计算三进制霍夫曼编码

[codes3, len3, process3] = huffman_code(symbols, P, 3);

% 三进制信源熵，单位 trit/symbol
H3 = H2 / log2(3);

% 三进制平均码长，单位 trit/symbol
L_avg3 = sum(P .* len3);

% 三进制编码效率
eta3 = H3 / L_avg3;

%% 输出二进制霍夫曼编码过程

fprintf('二进制霍夫曼编码合并过程\n\n');

for i = 1:length(process2)
    fprintf('第%-2d次合并：%-35s 合并后概率 = %.2f\n', ...
        i, process2(i).items, process2(i).weight);
end

fprintf('\n二进制霍夫曼编码结果\n\n');
fprintf('%-7s %-8s %-10s %-8s\n', '符号', '概率', '码字', '码长');
fprintf('----------------------------------------\n');

for i = 1:length(symbols)
    fprintf('%-8s %-10.2f %-12s %-8d\n', ...
        symbols{i}, P(i), codes2{i}, len2(i));
end

fprintf('\n信源熵 H(X)        = %.6f bit/symbol\n', H2);
fprintf('二进制平均码长 L   = %.6f bit/symbol\n', L_avg2);
fprintf('二进制编码效率 η   = %.2f%%\n', eta2 * 100);

%% 输出三进制霍夫曼编码过程

fprintf('\n\n三进制霍夫曼编码合并过程\n\n');

for i = 1:length(process3)
    fprintf('第%-2d次合并：%-35s 合并后概率 = %.2f\n', ...
        i, process3(i).items, process3(i).weight);
end

fprintf('\n三进制霍夫曼编码结果\n\n');
fprintf('%-7s %-8s %-10s %-8s\n', '符号', '概率', '码字', '码长');
fprintf('----------------------------------------\n');

for i = 1:length(symbols)
    fprintf('%-8s %-10.2f %-12s %-8d\n', ...
        symbols{i}, P(i), codes3{i}, len3(i));
end

fprintf('\n信源熵 H(X)        = %.6f bit/symbol\n', H2);
fprintf('三进制信源熵 H3(X) = %.6f trit/symbol\n', H3);
fprintf('三进制平均码长 L   = %.6f trit/symbol\n', L_avg3);
fprintf('三进制编码效率 η   = %.2f%%\n', eta3 * 100);


% D 进制霍夫曼编码函数

function [codes, lengths, process] = huffman_code(symbols, P, D)

    n = length(P);

    % 初始化码字
    codes = cell(1, n);
    for i = 1:n
        codes{i} = '';
    end

    % 判断是否需要补充虚符号
    padNum = mod((D - 1) - mod(n - 1, D - 1), D - 1);

    % 初始化节点
    nodes = struct('prob', {}, 'index', {}, 'name', {});

    for i = 1:n
        nodes(i).prob = P(i);
        nodes(i).index = i;
        nodes(i).name = symbols{i};
    end

    % 补充概率为 0 的虚符号
    for i = 1:padNum
        nodes(n + i).prob = 0;
        nodes(n + i).index = [];
        nodes(n + i).name = ['dummy' num2str(i)];
    end

    process = struct('items', {}, 'weight', {});

    step = 0;

    % 霍夫曼合并过程
    while length(nodes) > 1

        % 按概率从小到大排序
        [~, order] = sort([nodes.prob], 'ascend');
        nodes = nodes(order);

        % 取概率最小的 D 个节点
        selected = nodes(1:D);

        % 给 D 个分支分别赋 0,1,2,...
        for k = 1:D
            digit = num2str(k - 1);
            idx = selected(k).index;

            for m = 1:length(idx)
                codes{idx(m)} = [digit codes{idx(m)}];
            end
        end

        % 记录合并过程
        step = step + 1;

        nameList = cell(1, D);
        for k = 1:D
            nameList{k} = selected(k).name;
        end

        process(step).items = strjoin(nameList, ' + ');
        process(step).weight = sum([selected.prob]);

        % 生成新节点
        newNode.prob = sum([selected.prob]);
        newNode.index = [selected.index];
        newNode.name = ['(' strjoin(nameList, '+') ')'];

        % 删除已合并节点，并加入新节点
        nodes = [nodes(D+1:end), newNode];
    end

    % 计算码长
    lengths = zeros(1, n);
    for i = 1:n
        lengths(i) = length(codes{i});
    end
end