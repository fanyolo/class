clc; clear; close all;

f = '..\len.png';
img = imread(f);
if ndims(img)==3, img = uint8(0.299*img(:,:,1) + 0.587*img(:,:,2) + 0.114*img(:,:,3)); end
img = double(img) / 255;

%  2D 小波分解
[LL, LH, HL, HH] = haar_dwt2(img);

figure;
subplot(2,2,1); imagesc(LL); axis image off; colormap gray; title('LL');
subplot(2,2,2); imagesc(LH); axis image off; colormap gray; title('LH');
subplot(2,2,3); imagesc(HL); axis image off; colormap gray; title('HL');
subplot(2,2,4); imagesc(HH); axis image off; colormap gray; title('HH');

%   反变换重建
rec = haar_idwt2(LL, LH, HL, HH);

figure;
imagesc(rec); axis image off; colormap gray; title('反变换重建');



function [LL, LH, HL, HH] = haar_dwt2(x)
    [m,n] = size(x);

    if mod(m,2)==1, x(end+1,:) = x(end,:); m = m+1; end
    if mod(n,2)==1, x(:,end+1) = x(:,end); n = n+1; end

    s = sqrt(2);

    a = x(:,1:2:end);
    b = x(:,2:2:end);
    Lr = (a + b) / s;
    Hr = (a - b) / s;

 
    a = Lr(1:2:end,:);
    b = Lr(2:2:end,:);
    LL = (a + b) / s;
    LH = (a - b) / s;  

    a = Hr(1:2:end,:);
    b = Hr(2:2:end,:);
    HL = (a + b) / s;   % 高行低列
    HH = (a - b) / s;   % 高行高列
end

function x = haar_idwt2(LL, LH, HL, HH)
    s = sqrt(2);

  
    Lr = inv_haar_col(LL, LH, s);
    Hr = inv_haar_col(HL, HH, s);


    x  = inv_haar_row(Lr, Hr, s);
end

function y = inv_haar_col(L, H, s)
 
    [k, w] = size(L);
    y = zeros(2*k, w);

    y(1:2:end,:) = (L + H) / s;
    y(2:2:end,:) = (L - H) / s;
end

function y = inv_haar_row(L, H, s)
  
    [h, k] = size(L);
    y = zeros(h, 2*k);

    y(:,1:2:end) = (L + H) / s;
    y(:,2:2:end) = (L - H) / s;
end
