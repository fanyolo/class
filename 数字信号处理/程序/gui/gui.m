%%gui界面

f = figure('Position', [500, 500, 700, 500], 'Name', 'DTMF拨号音合成与识别', 'NumberTitle', 'off', 'Color', '#f0f0f0');


axes('Position', [0.1, 0.75, 0.2, 0.2]);  % 中南校徽
bg_image = imread('xiao.jpg'); 
imshow(bg_image, 'Border', 'tight');  

uicontrol('Style', 'text', 'Position', [220, 400, 300, 30], ...
    'FontSize', 16, 'String', 'DTMF拨号音合成与识别', ...
    'FontWeight', 'bold', 'ForegroundColor', '#2A4D72');

%输入框 实时显示
input_field = uicontrol('Style', 'edit', 'Position', [50,320, 180, 30], 'FontSize', 14, 'String', '', 'BackgroundColor', 'white', 'Callback', @(src, event) update_input(src.String, f)); 

keypad = {
    '1', '2', '3'; 
    '4', '5', '6'; 
    '7', '8', '9'; 
    '*', '0', '#'
};

button_color = [0.2 0.6 0.8]; 
for i = 1:4
    for j = 1:3
        uicontrol('Style', 'pushbutton', 'String', keypad{i,j}, 'Position', [50 + (j-1)*60, 250 - (i-1)*60, 50, 50], ...
            'FontSize', 14, 'FontWeight', 'bold', 'BackgroundColor', button_color, 'ForegroundColor', 'white', ...
            'Callback', @(src, event) append_to_input(input_field, src.String));
    end
end

% 删除 x
uicontrol('Style', 'pushbutton', 'String', 'x', 'Position', [50 + (1)*60, 10, 50, 50], ...
    'FontSize', 14, 'FontWeight', 'bold', 'BackgroundColor', button_color, 'ForegroundColor', 'white', ...
    'Callback', @(src, event) delete_last_character(input_field));

% 识别结果显示
recognition_display_1 = uicontrol('Style', 'text', 'Position', [450, 200, 200, 100], 'FontSize', 14, 'String', 'Goertzel算法识别结果:', 'BackgroundColor', '#f0f0f0', 'FontWeight', 'bold');
recognition_display_2 = uicontrol('Style', 'text', 'Position', [450, 100, 200, 100], 'FontSize', 14, 'String', '带通滤波器法识别结果:', 'BackgroundColor', '#f0f0f0', 'FontWeight', 'bold');



% 确认 保存 绘制 识别 文件
uicontrol('Style', 'pushbutton', 'String', '确认', 'Position', [300, 270, 100, 50], ...
    'FontSize', 14, 'BackgroundColor', '#4CAF50', 'FontWeight', 'bold', 'ForegroundColor', 'white', ...
    'Callback', @(src, event) play_and_save_dtmf(input_field.String, f));


uicontrol('Style', 'pushbutton', 'String', '保存拨号音', 'Position', [300, 210, 100, 50], ...
    'FontSize', 14, 'BackgroundColor', '#2196F3', 'FontWeight', 'bold', 'ForegroundColor', 'white', ...
    'Callback', @(src, event) save_dtmf_sound(f));


uicontrol('Style', 'pushbutton', 'String', '绘制波形', 'Position', [300, 150, 100, 50], ...
    'FontSize', 14, 'BackgroundColor', '#FF9800', 'FontWeight', 'bold', 'ForegroundColor', 'white', ...
    'Callback', @(src, event) plot_waveform(f));  


uicontrol('Style', 'pushbutton', 'String', '识别', 'Position', [300, 90, 100, 50], ...
    'FontSize', 14, 'BackgroundColor', '#FF5722', 'FontWeight', 'bold', 'ForegroundColor', 'white', ...
    'Callback', @(src, event) recognize_dtmf(input_field.String, f));

uicontrol('Style', 'pushbutton', 'String', '读取文件', 'Position', [300, 30, 100, 50], ...
    'FontSize', 14, 'FontWeight', 'bold', 'BackgroundColor', '#9C47B5', 'ForegroundColor', 'white', ...
    'Callback', @(src, event) read_and_recognize_dtmf(f));


% 数据
handles.input_field = input_field;
handles.recognition_display_1 = recognition_display_1;
handles.recognition_display_2 = recognition_display_2;
handles.sound_signal = [];  
guidata(f, handles); 




function save_dtmf_sound(f)
    handles = guidata(f);
    
    sound_signal = handles.sound_signal;
    
    % 没确认 没输入 报错
    if isempty(sound_signal)
        msgbox('没有生成拨号音，请先确认拨号!');
        return;
    end
    
    [file, path] = uiputfile('*.wav', '保存拨号音');
    
 
    if ischar(file)
        audiowrite(fullfile(path, file), sound_signal, 8000);  
        msgbox('拨号音已保存！');
    end
end




function read_and_recognize_dtmf(f)
   
    [file, path] = uigetfile('*.wav', '选择要读取的文件');
    if isequal(file, 0)
        return;
    end
    
    [sound_signal, fs] = audioread(fullfile(path, file));  % 读取音频数据
    
    % 调用文件识别函数处理
    recognize_dtmf_wav(sound_signal, fs, f);
end
