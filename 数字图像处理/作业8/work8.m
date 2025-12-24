clc; clear; close all;

% 输入图像
fpath = '..\test.png';    
f = imread(fpath);
if ndims(f) == 3
    f = uint8(0.299*f(:,:,1) + 0.587*f(:,:,2) + 0.114*f(:,:,3));
end
f = double(f) / 255;

[M,N] = size(f);
D = freqRadius(M,N);      

F = fftshift(fft2(f));


mnd = min(M,N);
params = [
    0.02*mnd   0.08*mnd   1.0
    0.04*mnd   0.12*mnd   1.0
    0.06*mnd   0.16*mnd   1.0
    0.04*mnd   0.12*mnd   1.8
];

K = size(params,1);

% 展示：每组参数两张图（上：带通分量  下：增强结果 f'）
figure;
tiledlayout(2, K, 'Padding','compact','TileSpacing','compact');

for i = 1:K
    s1 = params(i,1);
    s2 = params(i,2);
    a  = params(i,3);

    H = gaussBP(D, s1, s2);          % 高斯带通
    G = F .* H;
    g = real(ifft2(ifftshift(G)));  

    fp = f + a*g;                
    fp = clamp01(fp);

    gv = vis01(g);

    nexttile(i);
    imagesc(gv); axis image off; colormap gray;
    title(sprintf('GBP分量  \\sigma1=%.0f \\sigma2=%.0f', s1, s2));

    nexttile(K+i);
    imagesc(fp); axis image off; colormap gray;
    title(sprintf('f''  \\alpha=%.1f', a));
end


figure;
tiledlayout(1, K, 'Padding','compact','TileSpacing','compact');
for i = 1:K
    s1 = params(i,1); s2 = params(i,2);
    H = gaussBP(D, s1, s2);
    nexttile(i);
    imagesc(H); axis image off; colormap gray;
    title(sprintf('H(u,v) \\sigma1=%.0f \\sigma2=%.0f', s1, s2));
end



function D = freqRadius(M,N)
  
    u = (-floor(M/2)):(ceil(M/2)-1);
    v = (-floor(N/2)):(ceil(N/2)-1);
    [V,U] = meshgrid(v,u);
    D = sqrt(U.^2 + V.^2);
end

function H = gaussBP(D, s1, s2)
  
    H2 = exp(-(D.^2) / (2*s2*s2));
    H1 = exp(-(D.^2) / (2*s1*s1));
    H = H2 - H1;
end

function y = clamp01(x)
    y = x;
    y(y<0) = 0;
    y(y>1) = 1;
end

function y = vis01(x)
    % 把带通分量可视化到[0,1]：按均值±3σ压缩显示
    mu = mean(x(:));
    sg = std(x(:));
    a = mu - 3*sg; b = mu + 3*sg;
    if b <= a
        y = zeros(size(x));
        return;
    end
    y = (x - a) / (b - a);
    y = clamp01(y);
end
