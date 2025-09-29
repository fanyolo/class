%生成拨号音并播放

function play_dtmf(input_string)
    low_freq = [697, 770, 852, 941];   
    high_freq = [1209, 1336, 1477, 1633];
    keypad = {
        '1', '2', '3', 'A';
        '4', '5', '6', 'B';
        '7', '8', '9', 'C';
        '*', '0', '#', 'D';
    };

    fs = 8000; 
    tone_duration = 0.05; 
    silence_duration = 0.05; %静音

    sound_signal = [];

    
    for k = 1:length(input_string)
        key = input_string(k); 

        
        [row, col] = find(strcmp(keypad, key));
        
        
        if ~isempty(row) && ~isempty(col)
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
        end
    end
    
    
    if ~isempty(sound_signal)
        sound(sound_signal, fs);%播放
    end
end
