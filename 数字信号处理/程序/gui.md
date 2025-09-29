```
算法

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

%%Goertzel算法识别

function detected_key = detect_key_using_goertzel(signal, fs, keypad)
    low_freq = [697, 770, 852, 941];  
    high_freq = [1209, 1336, 1477, 1633];
    
   
    N = length(signal);  
    threshold = 0.1;  
    
    detected_key = '';
    

    low_freq_magnitude = zeros(1, length(low_freq)); 
    for i = 1:length(low_freq)
        low_freq_magnitude(i) = goertzel(signal, low_freq(i), fs, N);
    end
    
    
    high_freq_magnitude = zeros(1, length(high_freq));  
    for i = 1:length(high_freq)
        high_freq_magnitude(i) = goertzel(signal, high_freq(i), fs, N);
    end
    
   
    [max_low_freq_value, low_freq_index] = max(low_freq_magnitude);
    [max_high_freq_value, high_freq_index] = max(high_freq_magnitude);
    
    
    if max_low_freq_value > threshold && max_high_freq_value > threshold
        
        detected_key = keypad{low_freq_index, high_freq_index};  
    end
end

%Goertzel算法

function magnitude = goertzel(signal, target_freq, fs, N)
    k = round(0.5 + ((N * target_freq) / fs));
    w = 2 * pi * k / N;
    coeff = 2 * cos(w);
    s_prev = 0;
    s_prev2 = 0;
    
    for i = 1:N
        s = signal(i) + coeff * s_prev - s_prev2;
        s_prev2 = s_prev;
        s_prev = s;
    end
    
    magnitude = sqrt(s_prev^2 + s_prev2^2 - s_prev * s_prev2 * coeff);
end
%识别

function recognize_dtmf(input_string, f)
    low_freq = [697, 770, 852, 941];  
    high_freq = [1209, 1336, 1477, 1633]; 
    keypad = { 
        '1', '2', '3', 'A';
        '4', '5', '6', 'B';
        '7', '8', '9', 'C';
        '*', '0', '#', 'D';
    };
    key_sequence = input_string(:); 

    %读取的是字符串，先生成音频
    sound_signal = [];
    recognized_keys_goertzel = '';  
    recognized_keys_bandpass = ''; 

    fs = 8000;  
    tone_duration = 0.05; 
    silence_duration = 0.05; 

    for i = 1:length(key_sequence)
        key = key_sequence(i);
        
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
        fL = low_freq(row);  
        fH = high_freq(col); 
       
        t = 0:1/fs:tone_duration;  
        signal = sin(2*pi*fL*t) + sin(2*pi*fH*t);  
           
         noise_level = 0.05; 
        noise_signal = noise_level * randn(size(signal));  % 生成噪声
            signal_with_noise = signal + noise_signal;  % 将噪声加到信号上
            
            
            silence = zeros(1, round(silence_duration * fs)); 
            noise_silence = noise_level * randn(size(silence));  % 静音段的噪声
            silence_with_noise = silence + noise_silence;  % 将噪声加到静音段上

            % 合并信号和静音段
            sound_signal = [sound_signal, signal_with_noise, silence_with_noise]; 
        
        
        detected_key_goertzel = detect_key_using_goertzel(signal, fs, keypad);  % 传递 keypad
        recognized_keys_goertzel = [recognized_keys_goertzel, detected_key_goertzel];
        
      
        detected_key_bandpass = detect_key_using_bandpass(signal, fs, keypad);  % 传递 keypad
        recognized_keys_bandpass = [recognized_keys_bandpass, detected_key_bandpass];
    end

    
    sound(sound_signal, fs);
    disp('识别完成!');
    
    
    handles = guidata(f);
    
    % 显示
    handles.recognition_display_1.String = ['Goertzel算法: ', recognized_keys_goertzel];
    handles.recognition_display_2.String = ['带通滤波器法: ', recognized_keys_bandpass];
    
    guidata(f, handles);
end

```

