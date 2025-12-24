%% 作业11：自动找分隔线切图 + 计算 MSE/PSNR/SSIM
clc; clear; close all;

imgPath = 'work11.png'; 
I = imread(imgPath);
if size(I,3) == 1, I = repmat(I,[1 1 3]); end

[H,W,~] = size(I);


[s1, s2] = findSeparators(I);


L = I(:, 1:s1-1, :);
M = I(:, s1:s2-1, :);
R = I(:, s2:end, :);       


L = imresize(L, [size(R,1), size(R,2)]);
M = imresize(M, [size(R,1), size(R,2)]);


[mseL, psnrL, ssimL] = calcMetrics(L, R);
[mseM, psnrM, ssimM] = calcMetrics(M, R);

fprintf('自动分隔位置：s1=%d, s2=%d (图像宽度W=%d)\n', s1, s2, W);
fprintf('左图 vs 右标准:  MSE=%.6f, PSNR=%.6f dB, SSIM=%.6f\n', mseL, psnrL, ssimL);
fprintf('中图 vs 右标准:  MSE=%.6f, PSNR=%.6f dB, SSIM=%.6f\n', mseM, psnrM, ssimM);

% 切割结果
figure; imshow(L); title('Left (resized)');
figure; imshow(M); title('Middle (resized)');
figure; imshow(R); title('Right (Reference)');



function [s1, s2] = findSeparators(I)

    [~,W,~] = size(I);

    G = rgb2gray(I);
    colMean = mean(double(G), 1);             
    colMean = colMean / max(colMean + eps); 

    
    thr = max(0.92, prctile(colMean, 99));    
    bright = colMean >= thr;

 
    edge = max(5, round(0.03 * W));
    bright(1:edge) = false;
    bright(end-edge+1:end) = false;

    idx = find(bright);
    if isempty(idx)
     
        s1 = floor(W/3);
        s2 = floor(2*W/3);
        return;
    end


    breaks = [true, diff(idx) > 1, true];
    cutPos = find(breaks);
    segs = {};
    for k = 1:numel(cutPos)-1
        seg = idx(cutPos(k):cutPos(k+1)-1);
        segs{end+1} = seg; 
    end


    cand = [];
    for i = 1:numel(segs)
        seg = segs{i};
        w = numel(seg);
        c = mean(seg);

        if w <= round(0.05*W)
            cand = [cand; w, c];
        end
    end

    if size(cand,1) < 2
     
        s1 = floor(W/3);
        s2 = floor(2*W/3);
        return;
    end


    t1 = W/3; t2 = 2*W/3;


    [~, i1] = min(abs(cand(:,2) - t1));
    c1 = cand(i1,2);


    dist2 = abs(cand(:,2) - t2) + 1e6*(abs(cand(:,2) - c1) < 0.1*W);
    [~, i2] = min(dist2);
    c2 = cand(i2,2);


    s = sort([round(c1), round(c2)]);
    s1 = s(1);
    s2 = s(2);

    s1 = max(2, min(W-2, s1));
    s2 = max(s1+2, min(W-1, s2));
end

function [mseVal, psnrVal, ssimVal] = calcMetrics(testImg, refImg)

    if ~isa(testImg,'uint8'), testImg = im2uint8(testImg); end
    if ~isa(refImg,'uint8'),  refImg  = im2uint8(refImg);  end

    mseVal  = immse(testImg, refImg);
    psnrVal = psnr(testImg, refImg);
    ssimVal = ssim(testImg, refImg);
end
