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
