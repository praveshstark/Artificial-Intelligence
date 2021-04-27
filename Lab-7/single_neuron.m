%------------------------------------------------------------
% Single Neuron classifier
% Demonstration of on-line learning
% Stochastic gradient descent
%------------------------------------------------------------
clear all;
close all;

%--------Training DATA points with CLASS LABEL--------------
x = [1 1 1 1 1 1 1 1 1 1;2 3 3 5 5.5 5 7 8 9 9.5;3 2 6 3 4.5 6 4 6 7 5]';
t = [1 1 1 1 1 0 0 0 0 0]';

figure(1);
axis([0 10 0 10]);
hold on;
plot(x(1:5,2),x(1:5,3),'*');
plot(x(6:10,2),x(6:10,3),'o');
[x1,x2] = meshgrid(0:.1:10,0:.1:10);
hold off;
%-----------------------------------------------------------
%---- Single Neuron Classifier -----------------------------
%---------Gradient descent ---------------------------------

w = [0 0 0]';
L = 40000; % Number of iterations of GD
eta = 0.01;
for i=1:L
	a = x*w;
	y = my_activity(a); 
	e = t - y; % Error
	g = -x'*e;
	w = w - eta*g;	
	if mod(i,2000)==0
		figure(2);
		axis([0 10 0 10]);
		hold on;
		plot(x(1:5,2),x(1:5,3),'*');
		plot(x(6:10,2),x(6:10,3),'o');
		F = 1./(1.+exp(-(w(1)+w(2)*x1+w(3)*x2)));
		contour(x1,x2,F,3);
		hold off;
		pause(1);
	end
	GW(i) = -sum(t.*log(y) + (1-t).*log(1-y));
end

%F = 1./(1.+exp(-(w(1)+w(2)*x1+w(3)*x2)));
%contour(x1,x2,F,3);
%hold off;

figure(3); 
plot(1:L,GW);

figure(4);
axis([0 10 0 10]);
hold on;
plot(x(1:5,2),x(1:5,3),'*');
plot(x(6:10,2),x(6:10,3),'o');
contour(x1,x2,F,3);
hold off;

figure(5);
axis([0 10 0 10 0 1]); hold on;
plot(x(1:5,2),x(1:5,3),'*');
surf(x1,x2,F); hold off;





