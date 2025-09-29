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
