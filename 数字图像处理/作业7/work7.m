clc; clear; close all;

f = 'test.png';
img = imread(f);

out = enhance3sigma(img);

figure;
cmp = cat(2, img, out);   % 横向拼接
imshow(cmp);
title('左：原图   右：3\sigma增强');



function out = enhance3sigma(img)
    cls = class(img);


    x = to01(img);

    if ndims(x) == 2
        y = stretch3sigma_gray(x);
        out = from01(y, cls);
        return;
    end

  
    R = x(:,:,1); G = x(:,:,2); B = x(:,:,3);
    Y  = 0.299*R + 0.587*G + 0.114*B;

    Ye = stretch3sigma_gray(Y);

    epsv = 1e-8;
    ratio = Ye ./ (Y + epsv);

    Re = clamp01(R .* ratio);
    Ge = clamp01(G .* ratio);
    Be = clamp01(B .* ratio);

    out = from01(cat(3, Re, Ge, Be), cls);
end

function y = stretch3sigma_gray(x)
    % x in [0,1]
    [h,w] = size(x);
    n = h*w;

    % 计算均值
    s = 0;
    for i = 1:h
        for j = 1:w
            s = s + x(i,j);
        end
    end
    mu = s / n;

    % 计算标准差
    s2 = 0;
    for i = 1:h
        for j = 1:w
            d = x(i,j) - mu;
            s2 = s2 + d*d;
        end
    end
    sigma = sqrt(s2 / n);

    a = mu - 3*sigma;
    b = mu + 3*sigma;

    % 防止阈值越界
    if a < 0, a = 0; end
    if b > 1, b = 1; end

    % 防止除 0
    if b <= a
        y = x;
        return;
    end

    % clip + stretch
    y = zeros(h,w);
    for i = 1:h
        for j = 1:w
            v = x(i,j);
            if v < a, v = a; end
            if v > b, v = b; end
            y(i,j) = (v - a) / (b - a);
        end
    end
end

function x = to01(img)
    if isa(img,'uint8')
        x = double(img) / 255;
    elseif isa(img,'uint16')
        x = double(img) / 65535;
    else
        x = double(img);
        % 若输入本来不是[0,1]，简单归一化到[0,1]
        mn = min(x(:)); mx = max(x(:));
        if mx > mn
            x = (x - mn) / (mx - mn);
        else
            x = zeros(size(x));
        end
    end
    x = clamp01(x);
end

function out = from01(x, cls)
    x = clamp01(x);
    if strcmp(cls,'uint8')
        out = uint8(round(x * 255));
    elseif strcmp(cls,'uint16')
        out = uint16(round(x * 65535));
    else
        out = cast(x, cls);
    end
end

function y = clamp01(x)
    y = x;
    y(y < 0) = 0;
    y(y > 1) = 1;
end
