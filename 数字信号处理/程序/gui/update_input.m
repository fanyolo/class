%实时显示 输入框

function update_input(input_string, f)
    
    handles = guidata(f);
    handles.input_string = input_string;
    
    guidata(f, handles);
end
