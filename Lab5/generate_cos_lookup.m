clear all
close all

N = 1024;
n = 0:N-1;
alpha = 0.54;
beta = 0.46;
w = alpha - beta.*cos(2*pi*n/(N-1));
w = reshape(w,[32,32]);