% 电话拨号音合成
low_freq = [697, 770, 852, 941];   % 低频组
high_freq = [1209, 1336, 1477, 1633]; % 高频组

% 电话键盘映射 (每个按键对应低频和高频)
keypad = [
    1, 2, 3, 'A';
    4, 5, 6, 'B';
    7, 8, 9, 'C';
    '*', 0, '#', 'D';
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

for i = 1:length(key_sequence)
    key = key_sequence(i);
    
    % 根据按键值确定行和列
    if key == '1'
        row = 1; col = 1;
    elseif key == '2'
        row = 1; col = 2;
    elseif key == '3'
        row = 1; col = 3;
    elseif key == '4'
        row = 2; col = 1;
    elseif key == '5'
        row = 2; col = 2;
    elseif key == '6'
        row = 2; col = 3;
    elseif key == '7'
        row = 3; col = 1;
    elseif key == '8'
        row = 3; col = 2;
    elseif key == '9'
        row = 3; col = 3;
    elseif key == '0'
        row = 4; col = 2;
    elseif key == '*'
        row = 4; col = 1;
    elseif key == '#'
        row = 4; col = 3;
    elseif key == 'A'
        row = 1; col = 4;
    elseif key == 'B'
        row = 2; col = 4;
    elseif key == 'C'
        row = 3; col = 4;
    elseif key == 'D'
        row = 4; col = 4;
    end
    
    % 获取低频和高频
    fL = low_freq(row);  % 低频
    fH = high_freq(col); % 高频
    
    % 生成拨号音信号
    t = 0:1/fs:tone_duration;  % 时间向量
    signal = sin(2*pi*fL*t) + sin(2*pi*fH*t);  % 计算拨号音信号
    
    % 将拨号音信号与静音信号连接
    sound_signal = [sound_signal, signal, zeros(1, round(silence_duration * fs))];
end

% 播放合成的拨号音
sound(sound_signal, fs);

% 提示用户播放完成
disp('拨号音播放完成!');

% 绘制时域波形
figure;
subplot(2,1,1);

% 计算时间向量
time = (0:length(sound_signal)-1) / fs;  % 将样本转换为时间

% 绘制时域波形
plot(time, sound_signal);
title('拨号音时域波形');
xlabel('时间 (秒)');
ylabel('幅度');

% 绘制频域波形
N = length(sound_signal);
f = (0:N-1)*(fs/N);  % 频率向量
Y = abs(fft(sound_signal));  % 计算信号的幅度谱

subplot(2,1,2);
plot(f, Y);
title('拨号音频域波形');
xlabel('频率 (Hz)');
ylabel('幅度');
xlim([0 2000]);  % 限制频率范围在 0-2000Hz 以突出DTMF信号
