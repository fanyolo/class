% 让用户选择一个 wav 文件
[file, path] = uigetfile('*.wav', '选择一个音频文件');

if ~ischar(file)
    msgbox('没有选择文件');
    return;
end

% 读取选定的 wav 文件
[sound_signal, fs] = audioread(fullfile(path, file));

% 确保音频信号为单声道（如果是立体声，转换为单声道）
if size(sound_signal, 2) == 2
    sound_signal = mean(sound_signal, 2);  % 转换为单声道
end

% 绘制时域和频域波形
figure;

% 绘制时域波形
subplot(2,1,1);
time = (0:length(sound_signal)-1) / fs;  % 计算时间向量
plot(time, sound_signal);
title('音频信号时域波形');
xlabel('时间 (秒)');
ylabel('幅度');

% 绘制频域波形
N = length(sound_signal);
f = (0:N-1)*(fs/N);  % 频率向量
Y = abs(fft(sound_signal));  % 计算信号的幅度谱
subplot(2,1,2);
plot(f, Y);
title('音频信号频域波形');
xlabel('频率 (Hz)');
ylabel('幅度');
xlim([0 2000]);  % 限制频率范围在 0-2000Hz 以突出DTMF信号
