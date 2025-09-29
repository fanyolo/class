%读取文件处理

function recognize_dtmf_wav(sound_signal, fs, f)
    low_freq = [697, 770, 852, 941];   
    high_freq = [1209, 1336, 1477, 1633]; 
    keypad = {  
        '1', '2', '3', 'A';
        '4', '5', '6', 'B';
        '7', '8', '9', 'C';
        '*', '0', '#', 'D';
    };
    recognized_keys_goertzel = '';  
    recognized_keys_bandpass = '';  

    
    tone_duration = 0.05;  
    silence_duration = 0.05;  
    num_samples_per_tone = round(tone_duration * fs);
    num_samples_per_silence = round(silence_duration * fs);

    num_tones = floor(length(sound_signal) / (num_samples_per_tone + num_samples_per_silence));
    sound_signal = sound_signal(1:num_tones * (num_samples_per_tone + num_samples_per_silence));  % 截取有效部分

    
    for i = 1:num_tones
        start_idx = (i-1) * (num_samples_per_tone + num_samples_per_silence) + 1;
        end_idx = start_idx + num_samples_per_tone - 1;
        tone_signal = sound_signal(start_idx:end_idx);
        
        % Goertzel
        detected_key_goertzel = detect_key_using_goertzel(tone_signal, fs, keypad);
        recognized_keys_goertzel = [recognized_keys_goertzel, detected_key_goertzel];
        
        % 滤波器法
        detected_key_bandpass = detect_key_using_bandpass(tone_signal, fs, keypad);
        recognized_keys_bandpass = [recognized_keys_bandpass, detected_key_bandpass];
    end

    
    sound(sound_signal, fs);
    
    
    handles = guidata(f);
    
    set(handles.recognition_display_1, 'String', ['Goertzel算法: ', recognized_keys_goertzel]);
    set(handles.recognition_display_2, 'String', ['带通滤波器法: ', recognized_keys_bandpass]);
    
    guidata(f, handles);
end