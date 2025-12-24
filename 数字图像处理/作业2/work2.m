% 作业二：在 MATLAB 中用 imread、imshow 读入并显示一幅图

clc;           
clear;         
close all;      

% 1) 读入图像

filename = '..\len.png'; 

I = imread(filename);

% 2) 显示图像 
figure;                 
imshow(I);              
title('读入并显示的图像'); 