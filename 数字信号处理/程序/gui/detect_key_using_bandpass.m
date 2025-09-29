function detected_key = detect_key_using_bandpass(signal, fs, keypad)

    % DTMF 的低频和高频频率
    low_freq  = [697 770 852 941];
    high_freq = [1209 1336 1477 1633];

    BW  = 40;          % 带宽
    ORD = 4;           % 滤波器阶数
    MIN_DOM_RATIO = 3; % 最小主导比率
    ABS_THR = 1e-2;    % 能量绝对阈值
    
    x = signal(:);
    Ptot = mean(x.^2) + eps;  % 信号总功率

    lowE  = zeros(1, numel(low_freq));
    highE = zeros(1, numel(high_freq));


    disp('计算低频频率的能量：');
    for i = 1:numel(low_freq)
        y = bandpass_narrow(x, fs, low_freq(i), BW, ORD);
        lowE(i) = mean(y.^2) / Ptot;
        disp(['    低频 ', num2str(low_freq(i)), ' Hz 的能量为: ', num2str(lowE(i))]); % 输出每个低频的能量
    end


    disp('计算高频频率的能量：');
    for i = 1:numel(high_freq)
        y = bandpass_narrow(x, fs, high_freq(i), BW, ORD);
        highE(i) = mean(y.^2) / Ptot;
        disp(['    高频 ', num2str(high_freq(i)), ' Hz 的能量为: ', num2str(highE(i))]); % 输出每个高频的能量
    end


    [maxL, idxL] = max(lowE);
    [maxH, idxH] = max(highE);
    

    if numel(lowE) > 1
        secL = max(lowE([1:idxL-1, idxL+1:end]));
    else
        secL = 0;
    end
    if numel(highE) > 1
        secH = max(highE([1:idxH-1, idxH+1:end]));
    else
        secH = 0;
    end


    ok = (maxL > ABS_THR) && (maxH > ABS_THR) && ...
         (maxL/(secL + eps) >= MIN_DOM_RATIO) && ...
         (maxH/(secH + eps) >= MIN_DOM_RATIO);

 
    if ok
        disp(['检测到按键: ', keypad{idxL, idxH}]); % 输出识别的按键
        detected_key = keypad{idxL, idxH};
    else
        disp('未能有效识别按键'); % 输出未识别结果
        detected_key = '';
    end
end


function y = bandpass_narrow(x, fs, f0, BW, ORD)
    % 带通滤波器实现
    f1 = max(1,       f0 - BW);  % 低频下限
    f2 = min(fs/2-1,  f0 + BW);  % 高频上限
    Wn = [f1, f2] / (fs/2);      % 归一化频率范围
    Wn = min(max(Wn, 1e-6), 0.999999);   
    if Wn(2) <= Wn(1)
        Wn(2) = min(0.999999, Wn(1) + 1e-3);
    end
    [b,a] = butter(ORD, Wn, 'bandpass');  % 巴特沃斯滤波器设计
    y = filtfilt(b, a, x);                 % 对信号应用滤波器
end
