%删除

function delete_last_character(input_field)
    current_input = input_field.String;
    if ~isempty(current_input)
        input_field.String = current_input(1:end-1);  
    end
end
