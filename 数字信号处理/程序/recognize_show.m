% 电话拨号音合成
low_freq = [697, 770, 852, 941];   % 低频组
high_freq = [1209, 1336, 1477, 1633]; % 高频组

% 电话键盘映射 (每个按键对应低频和高频)
keypad = [
    '1', '2', '3', 'A';
    '4', '5', '6', 'B';
    '7', '8', '9', 'C';
    '*', '0', '#', 'D';
];

% 用户输入按键 (模拟拨号音)，可以输入连续数字
key_input = input('请输入要合成的拨号音（可以输入连续数字）：', 's');

% 去除输入中的空格
key_input = strrep(key_input, ' ', '');

% 将输入转换为字符数组
key_sequence = key_input(:);  % 每个字符作为一个按键

% 确保输入的每个字符都是合法的
valid_keys = ['0':'9', '*', '#', 'A', 'B', 'C', 'D'];  % 有效的按键字符
if any(~ismember(key_sequence, valid_keys))
    disp('输入无效，请输入有效的数字序列或符号（*、#、A、B、C、D）。');
    return;
end

% 采样频率
fs = 8000;  % 采样频率为8kHz

% 每个按键音频信号的持续时间 (单位：秒)
tone_duration = 0.05;  % 持续时间 50ms
% 静音时间 (单位：秒)
silence_duration = 0.05;  % 静音时间 50ms（100ms - 50ms音频时长）

% 合成拨号音
sound_signal = [];
recognized_keys = '';  % 用于存储识别的按键

for i = 1:length(key_sequence)
    key = key_sequence(i);
    
    % 根据按键值确定行和列
    switch key
        case '1', row = 1; col = 1;
        case '2', row = 1; col = 2;
        case '3', row = 1; col = 3;
        case '4', row = 2; col = 1;
        case '5', row = 2; col = 2;
        case '6', row = 2; col = 3;
        case '7', row = 3; col = 1;
        case '8', row = 3; col = 2;
        case '9', row = 3; col = 3;
        case '0', row = 4; col = 2;
        case '*', row = 4; col = 1;
        case '#', row = 4; col = 3;
        case 'A', row = 1; col = 4;
        case 'B', row = 2; col = 4;
        case 'C', row = 3; col = 4;
        case 'D', row = 4; col = 4;
    end
    
    % 获取低频和高频
    fL = low_freq(row);  % 低频
    fH = high_freq(col); % 高频
    
    % 生成拨号音信号
    t = 0:1/fs:tone_duration;  % 时间向量
    signal = sin(2*pi*fL*t) + sin(2*pi*fH*t);  % 计算拨号音信号
    noise_level = 0.006; 
    noise_signal = noise_level * randn(size(signal));  % 生成噪声
            signal_with_noise = signal + noise_signal;  % 将噪声加到信号上
            
            
            silence = zeros(1, round(silence_duration * fs)); 
            noise_silence = noise_level * randn(size(silence));  % 静音段的噪声
            silence_with_noise = silence + noise_silence;  % 将噪声加到静音段上

            % 合并信号和静音段
            sound_signal = [sound_signal, signal_with_noise, silence_with_noise]; 
    
    % 调用Goertzel算法进行频率检测
    detected_key = detect_key_using_goertzel(signal, fs);
    
    % 将识别的按键添加到识别结果中
    recognized_keys = [recognized_keys, detected_key];
end

% 播放合成的拨号音
sound(sound_signal, fs);
disp('拨号音播放完成!');




%% Goertzel算法
% 输出识别的拨号音
disp('Goertzel算法拨号音：');
disp(recognized_keys);
% Goertzel算法识别函数
function [detected_key] = detect_key_using_goertzel(signal, fs)
    % 双音多频信号的频率
    low_freq = [697, 770, 852, 941];   % 低频组
    high_freq = [1209, 1336, 1477, 1633]; % 高频组
    
    % Goertzel算法参数
    N = length(signal);  % 信号长度
    threshold = 0.1;  % 阈值，设定为较低的幅度值，用于判断是否为该频率
    
    detected_key = '';
    
    % 识别低频
    low_freq_magnitude = zeros(1, length(low_freq));  % 存储低频幅度
    for i = 1:length(low_freq)
        low_freq_magnitude(i) = goertzel(signal, low_freq(i), fs, N);
    end
    
    % 识别高频
    high_freq_magnitude = zeros(1, length(high_freq));  % 存储高频幅度
    for i = 1:length(high_freq)
        high_freq_magnitude(i) = goertzel(signal, high_freq(i), fs, N);
    end
    
    % 查找最大幅度对应的频率
    [max_low_freq_value, low_freq_index] = max(low_freq_magnitude);
    [max_high_freq_value, high_freq_index] = max(high_freq_magnitude);
    
    % 如果低频和高频的幅度都大于设定的阈值，则认为找到了按键
    if max_low_freq_value > threshold && max_high_freq_value > threshold
        % 映射到键盘上
        keypad = [
            '1', '2', '3', 'A';
            '4', '5', '6', 'B';
            '7', '8', '9', 'C';
            '*', '0', '#', 'D';
        ];
        
        % 得到按键
        detected_key = keypad(low_freq_index, high_freq_index);
    end
end

% Goertzel算法实现
function magnitude = goertzel(signal, target_freq, fs, N)
    % 计算Goertzel算法的结果
    k = round(0.5 + ((N * target_freq) / fs));  % 目标频率对应的k值
    w = 2 * pi * k / N;  % 角频率
    coeff = 2 * cos(w);  % 系数
    
    % 初始化
    s_prev = 0;
    s_prev2 = 0;
    
    % 计算Goertzel算法
    for i = 1:N
        s = signal(i) + coeff * s_prev - s_prev2;
        s_prev2 = s_prev;
        s_prev = s;
    end
    
    % 计算幅度
    magnitude = sqrt(s_prev^2 + s_prev2^2 - s_prev * s_prev2 * coeff);
end

function magnitude = goertzel_power_spectrum(signal, target_freq, fs)
    % 计算Goertzel算法的功率谱
    N = length(signal);  % 信号长度
    k = round(0.5 + ((N * target_freq) / fs));  % 目标频率对应的k值
    w = 2 * pi * k / N;  % 角频率
    coeff = 2 * cos(w);  % 系数
    
    % 初始化
    s_prev = 0;
    s_prev2 = 0;
    magnitude = zeros(1, N);  % 存储幅度值
    
    % 计算Goertzel算法
    for i = 1:N
        s = signal(i) + coeff * s_prev - s_prev2;
        s_prev2 = s_prev;
        s_prev = s;
        
        % 计算每个点的功率谱
        magnitude(i) = s_prev^2 + s_prev2^2 - s_prev * s_prev2 * coeff;
    end
end


%% 带通滤波器法
% 设计带通滤波器
bandwidth = 20; % 带通滤波器带宽
detected_keys_bandpass = [];
for i = 1:length(key_sequence)
    key = key_sequence(i);
    
    [row, col] = find(keypad == key);  % 查找对应的行列
    
    fL = low_freq(row);
    fH = high_freq(col);
    
    % 设计低频和高频带通滤波器
    [bL, aL] = butter(4, [(fL-0.5)/(fs/2), (fL+0.5)/(fs/2)], 'bandpass');
    [bH, aH] = butter(4, [(fH-0.5)/(fs/2), (fH+0.5)/(fs/2)], 'bandpass');
    
    % 使用带通滤波器提取频率成分
    signal_L = filter(bL, aL, sound_signal);
    signal_H = filter(bH, aH, sound_signal);
    
    % 计算能量
    energy_L = sum(signal_L.^2);
    energy_H = sum(signal_H.^2);
    
    % 输出识别的频率
    if energy_L > energy_H
        detected_keys_bandpass = [detected_keys_bandpass, keypad(row, col)];
    else
        detected_keys_bandpass = [detected_keys_bandpass, keypad(row, col)];
    end
end

disp('带通滤波器法识别的按键：');
disp(detected_keys_bandpass);



% Goertzel算法功率谱估计
figure;
hold on;
for i = 1:length(low_freq)
    % 计算低频和高频的功率谱
    low_freq_magnitude = goertzel_power_spectrum(sound_signal, low_freq(i), fs);
    high_freq_magnitude = goertzel_power_spectrum(sound_signal, high_freq(i), fs);
    
    % 绘制功率谱
    plot(low_freq(i) * ones(1, length(low_freq_magnitude)), low_freq_magnitude, 'r', 'LineWidth', 2);
    plot(high_freq(i) * ones(1, length(high_freq_magnitude)), high_freq_magnitude, 'b', 'LineWidth', 2);
end
hold off;
title('DTMF信号的功率谱 (Goertzel算法)');
xlabel('频率 (Hz)');
ylabel('幅度');
legend('低频', '高频');
grid on;

