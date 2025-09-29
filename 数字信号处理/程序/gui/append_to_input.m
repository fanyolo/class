%每一个数字按键的声音

function append_to_input(input_field, key)
    current_input = input_field.String;
    input_field.String = [current_input, key];
    
    % 调用播放函数
    play_dtmf(key);
end
