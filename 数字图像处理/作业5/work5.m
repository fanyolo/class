clc; clear; close all;

f = '..\len.png';
img = imread(f);
if ndims(img)==3, img = rgb2gray(img); end
img = im2double(img);

% 补零到 2 的幂
[m,n] = size(img);
p = 2^nextpow2(m);
q = 2^nextpow2(n);
x = zeros(p,q);
x(1:m,1:n) = img;

% 自写二维 FFT：先行后列
F  = myfft2(x);
Fs = fftshift(F);         

A = log(1 + abs(Fs));      
P = angle(Fs);              
P = (P + pi) / (2*pi);      

figure; imshow(A,[]); title('幅值');
figure; imshow(P,[]); title('相位');



function Y = myfft2(X)
% 2D FFT = 对每行做 1D FFT，再对每列做 1D FFT
[h,w] = size(X);
Y = complex(zeros(h,w));
for i = 1:h
    Y(i,:) = myfft1(X(i,:));
end
for j = 1:w
    Y(:,j) = myfft1(Y(:,j).').';
end
end

function X = myfft1(x)

x = complex(x(:));
N = length(x);

X = x(bitrev_idx(N));     

m = 2;
while m <= N
    h = m/2;
    W = exp(-2i*pi*(0:h-1)/m).';   % 旋转因子
    for k = 1:m:N                 % 蝶形运算
        u = X(k:k+h-1);
        t = W .* X(k+h:k+m-1);
        X(k:k+h-1)   = u + t;
        X(k+h:k+m-1) = u - t;
    end
    m = m*2;
end
X = X.';
end

function idx = bitrev_idx(N)

b = log2(N);
idx = zeros(1,N);
for i = 0:N-1
    r = 0; v = i;
    for t = 1:b
        r = bitshift(r,1) + bitand(v,1);
        v = bitshift(v,-1);
    end
    idx(i+1) = r + 1;
end
end
