clc; clear; close all;

f = '..\len.png';       
img = imread(f);

% 转灰度并归一化到[0,1]
x = toGray01(img);

% Sobel 边缘
th = 0.25;                 
[mag, edge] = sobelEdge(x, th);

% 显示
figure('Color','w');
tiledlayout(1,3,'Padding','compact','TileSpacing','compact');

nexttile; imagesc(x); axis image off; colormap gray; title('原图(灰度)');
nexttile; imagesc(mag); axis image off; colormap gray; title('Sobel 幅值');
nexttile; imagesc(edge); axis image off; colormap gray;
title(sprintf('Sobel 边缘(阈值=%.2f)', th));

% 保存
imwrite(uint8(round(mag*255)), 'lena_sobel_mag.png');
imwrite(uint8(edge*255),       'lena_sobel_edge.png');



function x = toGray01(img)
    if ndims(img)==3
        img = 0.299*double(img(:,:,1)) + 0.587*double(img(:,:,2)) + 0.114*double(img(:,:,3));
    else
        img = double(img);
    end
    x = img / 255;
    x = clamp01(x);
end

function [mag, edge] = sobelEdge(x, th)
    % Sobel核
    kx = [-1 0 1; -2 0 2; -1 0 1];
    ky = [-1 -2 -1; 0 0 0; 1 2 1];

    gx = myConv2(x, kx);
    gy = myConv2(x, ky);

    mag = sqrt(gx.^2 + gy.^2);
   
    mag = mag / (max(mag(:)) + 1e-12);

    edge = mag >= th;   % 二值边缘
end

function y = myConv2(x, k)
  
    [H,W] = size(x);
    [kh,kw] = size(k);
    ph = floor(kh/2);
    pw = floor(kw/2);

    xp = padReplicate(x, ph, pw);

    y = zeros(H,W);
    for r = 1:H
        for c = 1:W
            s = 0;
            for i = 1:kh
                for j = 1:kw
                    s = s + xp(r+i-1, c+j-1) * k(i,j);
                end
            end
            y(r,c) = s;
        end
    end
end

function xp = padReplicate(x, ph, pw)
    [H,W] = size(x);
    xp = zeros(H+2*ph, W+2*pw);

    for r = 1:(H+2*ph)
        rr = r - ph;
        if rr < 1, rr = 1; end
        if rr > H, rr = H; end
        for c = 1:(W+2*pw)
            cc = c - pw;
            if cc < 1, cc = 1; end
            if cc > W, cc = W; end
            xp(r,c) = x(rr,cc);
        end
    end
end

function y = clamp01(x)
    y = x;
    y(y<0) = 0;
    y(y>1) = 1;
end
