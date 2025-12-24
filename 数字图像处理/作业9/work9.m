clc; clear; close all;

f = '..\len.png';
img = imread(f);

% 转灰度
if ndims(img)==3
    img = uint8(0.299*img(:,:,1) + 0.587*img(:,:,2) + 0.114*img(:,:,3));
end
x = double(img)/255;

% 参数
sig = 0.08;     % 高斯噪声标准差
peak = 30;      % 泊松噪声
d = 0.03;       % 椒盐噪声密度
A = 0.12;       % 均匀噪声幅度 

g = addGaussian(x, sig);
p = addPoisson(x, peak);
sp = addSaltPepper(x, d);
u = addUniform(x, A);

% 显示并标注参数
figure;
tiledlayout(2,2,'Padding','compact','TileSpacing','compact');

nexttile; imagesc(g); axis image off; colormap gray;
title(sprintf('高斯噪声 ', sig));

nexttile; imagesc(p); axis image off; colormap gray;
title(sprintf('泊松噪声 ', peak));

nexttile; imagesc(sp); axis image off; colormap gray;
title(sprintf('椒盐噪声', d));

nexttile; imagesc(u); axis image off; colormap gray;
title(sprintf('均匀噪声', A));

% 保存
imwrite(uint8(round(g*255)),  'lena_gaussian.png');
imwrite(uint8(round(p*255)),  'lena_poisson.png');
imwrite(uint8(round(sp*255)), 'lena_saltpepper.png');
imwrite(uint8(round(u*255)),  'lena_uniform.png');



function y = addGaussian(x, sigma)
    y = x + sigma*randn(size(x));
    y = clamp01(y);
end

function y = addUniform(x, A)
    y = x + (2*rand(size(x)) - 1)*A;   % [-A, +A]
    y = clamp01(y);
end

function y = addSaltPepper(x, d)
    y = x;
    r = rand(size(x));
    y(r < d/2) = 0;           % pepper
    y(r > 1-d/2) = 1;         % salt
    y = clamp01(y);
end

function y = addPoisson(x, peak)
    
    lam = x * peak;
    y = zeros(size(x));

    
    small = lam < 30;
    y(small) = poisson_knuth(lam(small)) / peak;

    big = ~small;
    if any(big(:))
        lb = lam(big);
        k = round(lb + sqrt(lb).*randn(size(lb)));  % 近似 Poisson
        k(k<0) = 0;
        y(big) = k / peak;
    end

    y = clamp01(y);
end

function k = poisson_knuth(lam)
   
    k = zeros(size(lam));
    for idx = 1:numel(lam)
        L = exp(-lam(idx));
        p = 1;
        c = 0;
        while p > L
            c = c + 1;
            p = p * rand();
        end
        k(idx) = c - 1;
    end
end

function y = clamp01(x)
    y = x;
    y(y<0) = 0;
    y(y>1) = 1;
end
