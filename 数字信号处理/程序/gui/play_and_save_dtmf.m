% 保存识别的信号

function play_and_save_dtmf(input_string, f)
    low_freq = [697, 770, 852, 941];  
    high_freq = [1209, 1336, 1477, 1633]; 
    keypad = { 
        '1', '2', '3', 'A';
        '4', '5', '6', 'B';
        '7', '8', '9', 'C';
        '*', '0', '#', 'D';
    };

    key_sequence = input_string(:); 

    sound_signal = [];
    fs = 8000;  
    tone_duration = 0.05;  
    silence_duration = 0.05;  
    noise_level = 0.001; 

    for k = 1:length(key_sequence)
        key = key_sequence(k); 
        [row, col] = find(strcmp(keypad, key));
        
        if ~isempty(row) && ~isempty(col)
            fL = low_freq(row);
            fH = high_freq(col); 
            t = 0:1/fs:tone_duration; 
            signal = sin(2*pi*fL*t) + sin(2*pi*fH*t); 
            
          
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
        sound(sound_signal, fs);
    end
    
    handles = guidata(f);
    handles.sound_signal = sound_signal; 
    guidata(f, handles);  
end
