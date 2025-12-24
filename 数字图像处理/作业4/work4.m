clc; clear; close all;

filename = '..\len.png';
I = imread(filename);

theta = 45;
rad = deg2rad(theta);

I = im2double(I);
[H, W, C] = size(I);

% 原图中心
cx = (W+1)/2; 
cy = (H+1)/2;

% 计算“loose”输出尺寸：旋转四角求包围盒
corners = [1,1; W,1; 1,H; W,H];
x = corners(:,1) - cx;
y = corners(:,2) - cy;

xr = x*cos(rad) - y*sin(rad);
yr = x*sin(rad) + y*cos(rad);

minx = min(xr); maxx = max(xr);
miny = min(yr); maxy = max(yr);

W2 = ceil(maxx - minx + 1);
H2 = ceil(maxy - miny + 1);

% 新图中心
cx2 = (W2+1)/2;
cy2 = (H2+1)/2;

J = zeros(H2, W2, C);

% 输出图坐标
[XX, YY] = meshgrid(1:W2, 1:H2);
x2 = XX - cx2;
y2 = YY - cy2;

% 逆变换（映射回原图）
x1 = x2*cos(rad) + y2*sin(rad);
y1 = -x2*sin(rad) + y2*cos(rad);

Xsrc = x1 + cx;
Ysrc = y1 + cy;

% 双线性插值
for k = 1:C
    J(:,:,k) = bilinearSample(I(:,:,k), Xsrc, Ysrc);
end

J8 = im2uint8(J);

figure;
imshow(J8);
title('逆时针旋转45°');

% ===== 双线性采样函数 =====
function out = bilinearSample(img, X, Y)
    [H, W] = size(img);
    out = zeros(size(X));

    valid = (X >= 1) & (X <= W) & (Y >= 1) & (Y <= H);
    Xv = X(valid); Yv = Y(valid);

    x1 = floor(Xv); x2 = min(x1 + 1, W);
    y1 = floor(Yv); y2 = min(y1 + 1, H);

    dx = Xv - x1;
    dy = Yv - y1;

    Ia = img(sub2ind([H,W], y1, x1));
    Ib = img(sub2ind([H,W], y1, x2));
    Ic = img(sub2ind([H,W], y2, x1));
    Id = img(sub2ind([H,W], y2, x2));

    out(valid) = (1-dx).*(1-dy).*Ia + dx.*(1-dy).*Ib + (1-dx).*dy.*Ic + dx.*dy.*Id;
end
