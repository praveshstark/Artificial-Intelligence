% Demo exercise: CS308 Introduction to AI
%
% (Conditional) Markov Random Field for Image Denoising
%
%-------------------------------------------------------------

clear all;
close all;

%I = imread("noisy_checkerboard_mrf.jpg");
%[M,N] = size(I);

I(1:100,1:50) = 150+10*randn(100,50);
I(1:100,51:100) = 50 + 10*randn(100,50);

Inew = I;
iter_max = 1000;
lamda = 5;
mu = .1;

for iteration=1:iter_max
    E1 = sum(sum((Inew-I).^2));
    E2 = sum(sum(diff(Inew,1,1).^2))+sum(sum(diff(Inew,1,2).^2));
    E(iteration)=E1+E2;
    z1 = Inew-I; 
    s1 = sqrt(10);
    z2 = 2*Inew-circshift(Inew,-1,1)-circshift(Inew,-1,2); 
    s2 = sqrt(10);
    Grad = 2*z1./(z1.^2+2*s1^2) + lamda*2*z2./(z2.^2+2*s2^2);
    Inew = Inew - mu*Grad;
end

figure(1);
subplot(1,2,1);imshow(uint8(I));
subplot(1,2,2);imshow(uint8(Inew));
