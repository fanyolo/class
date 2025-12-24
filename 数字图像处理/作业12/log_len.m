clc; clear; close all;

f = '..\len.png';            
img = imread(f);

% 转灰度并归一化
x = toGray01(img);


sigma = 1.4;              
ksize = 9;                  
zc_th = 0.03;             

% LoG 边缘
[resp, edge] = logEdge(x, sigma, ksize, zc_th);

% 显示
figure('Color','w');
tiledlayout(1,3,'Padding','compact','TileSpacing','compact');

nexttile; imagesc(x); axis image off; colormap gray; title('原图(灰度)');
nexttile; imagesc(resp); axis image off; colormap gray;
title(sprintf('LoG 响应(\\sigma=%.1f, k=%d)', sigma, ksize));
nexttile; imagesc(edge); axis image off; colormap gray;
title(sprintf('LoG 零交叉边缘(阈值=%.3f)', zc_th));


resp_vis = resp;
mn = min(resp_vis(:)); mx = max(resp_vis(:));
resp_vis = (resp_vis - mn) / (mx - mn + 1e-12);

imwrite(uint8(round(resp_vis*255)), 'lena_log_resp.png');
imwrite(uint8(edge*255),            'lena_log_edge.png');



function x = toGray01(img)
    if ndims(img)==3
        img = 0.299*double(img(:,:,1)) + 0.587*double(img(:,:,2)) + 0.114*double(img(:,:,3));
    else
        img = double(img);
    end
    x = img / 255;
    x = clamp01(x);
end

function [resp, edge] = logEdge(x, sigma, ksize, zc_th)
    k = makeLoGKernel(ksize, sigma); 
    resp = myConv2(x, k);            


    edge = zeroCrossing(resp, zc_th);
end

function k = makeLoGKernel(ksize, sigma)
    r = floor(ksize/2);
    s2 = sigma^2; s4 = s2^2;

    k = zeros(ksize, ksize);
    sumk = 0;
    for y = -r:r
        for x = -r:r
            rr = x*x + y*y;
            val = ((rr - 2*s2)/s4) * exp(-rr/(2*s2));
            k(y+r+1, x+r+1) = val;
            sumk = sumk + val;
        end
    end

    k = k - sumk/(ksize*ksize);
end

function edge = zeroCrossing(resp, th)
    [H,W] = size(resp);
    edge = false(H,W);


    for r = 2:H-1
        for c = 2:W-1
            nb = resp(r-1:r+1, c-1:c+1);
            mn = min(nb(:));
            mx = max(nb(:));

            if (mn < 0) && (mx > 0) && ((mx - mn) >= th)
                edge(r,c) = true;
            end
        end
    end
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
