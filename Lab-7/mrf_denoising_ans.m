% Demo exercise: CS308 Introduction to AI
%
% (Conditional) Markov Random Field for Image Denoising
%
%-------------------------------------------------------------

clear all;
close all;
I = imread("cameraman.tif");
[M,N] = size(I);

I=im2double(I)+randn(size(I))*0.1;
Inew=I;

iter_max = 1000;
lamda = 5;
mu = .1;

for iteration=1:iter_max
    E1 = sum((Inew-I).^2);
    E2 = sum(sum(diff(Inew,11).^2))+sum(sum(diff(Inew,1,2).^2));
   
    z1 = Inew-I; 
    s1 = sqrt(10);
    z2 = 2*Inew-circshift(Inew,-1,1)-circshift(Inew,-1,2); 
    s2 = sqrt(10);
    Grad = 2*z1./(z1.^2+2*s1^2) + lamda*2*z2./(z2.^2+2*s2^2);
    Inew = Inew - mu*Grad;
end

figure(1);
subplot(1,2,1);imshow(I);
subplot(1,2,2);imshow(Inew);
