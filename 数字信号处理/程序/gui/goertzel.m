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
