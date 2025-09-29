function plot_waveform_and_spectrogram(f)
   
    handles = guidata(f);
    sound_signal = handles.sound_signal;
    
    if isempty(sound_signal)
        msgbox('没有合成拨号音，请先输入拨号音。');
        return;
    end
    
    fs = 8000; 
    
    % 创建一个图形窗口，绘制时域波形和频域波形
    figure;
    
    % 时域波形
    subplot(2,1,1);
    time = (0:length(sound_signal)-1) / fs;  % 将样本转换为时间
    plot(time, sound_signal);
    title('拨号音时域波形');
    xlabel('时间 (秒)');
    ylabel('幅度');
    
    % 频域波形
    N = length(sound_signal);
    f = (0:N-1)*(fs/N);  
    Y = abs(fft(sound_signal));  
    subplot(2,1,2);
    plot(f, Y);
    title('拨号音频域波形');
    xlabel('频率 (Hz)');
    ylabel('幅度');
    xlim([0 2000]); 
    
    % 单独显示时频图
    figure;
    spectrogram(sound_signal, 256, 200, 256, fs, 'yaxis');
    title('拨号音时频图');
    xlabel('时间 (秒)');
    ylabel('频率 (Hz)');
end
