% 作业3：图像平移
clc; clear; close all;

f = '..\len.png';
I = imread(f);

dx = 5;   % 右移
dy = 10;  % 下移

J = myShift(I, dx, dy);

imshow(J);
title('右移5像素，下移10像素');


function J = myShift(I, dx, dy)
    % dx>0 右移，dx<0 左移；dy>0 下移，dy<0 上移
    [h,w,c] = size(I);
    J = zeros(h,w,c, 'like', I);

    for y = 1:h
        for x = 1:w
            ys = y - dy;     % 反向映射：目标(y,x)来自原图(ys,xs)
            xs = x - dx;

            if ys >= 1 && ys <= h && xs >= 1 && xs <= w
                for k = 1:c
                    J(y,x,k) = I(ys,xs,k);
                end
            end
        end
    end
end
