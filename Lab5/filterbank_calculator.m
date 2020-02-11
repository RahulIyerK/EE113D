clear all
close all

num_filters = 26;

phi_0 = 250;
phi_max = 8000;

fmel_0 = 2595 * log10(1 + phi_0/700);
fmel_max = 2595 * log10(1 + phi_max/700);

band_unit_spacing = (fmel_max - fmel_0) / (num_filters + 1); % mel

fmels = fmel_0:band_unit_spacing:fmel_max;

phis = 700.*((10.^(fmels/2595))-1);

pos_slopes = zeros(1,num_filters);
neg_slopes = zeros(1,num_filters);

for i = 1:num_filters
    pos_slopes(1,i) = 1/(phis(1,i+1) - phis(1,i));
end

for i = 1:num_filters
    neg_slopes(1,i) = -1/(phis(1,i+2) - phis(1,i+1));
end

peaks = phis(1,2:27);


% for each triangle
%     find start index of psd and psd index before peak
%     find index after peak and end index of psd
%     
%     use positive slope and linear interpolation to multiply and accumulate
%         on positive slope
%         
%     use negative slope ... on negative slope
%         
% 
%     sum positive and negative MACs
%     
%     store sum into "Y" array
%     
%     store log "Y" into "X"
% 
% DCT on "X" array
    
    