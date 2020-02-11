clear all

% load input data
aah_data = load('../training_data/preprocessed_data/aah_mfcc.dat');
eh_data =  load('../training_data/preprocessed_data/eh_mfcc.dat');
ee_data =  load('../training_data/preprocessed_data/ee_mfcc.dat');
oo_data =  load('../training_data/preprocessed_data/oo_mfcc.dat');

input = zeros(40,13);

for i=1:10
    for j=0:12
        input(i,j) = aah_data(i+j,1);
    end
end

for i=1:10
    for j=1:13
        input(i,j) = eh_data(i+j,1);
    end
end

for i=1:10
    for j=1:13
        input(i,j) = aah_data(i+j,1);
    end
end
for i=1:10
    for j=1:13
        input(i,j) = aah_data(i+j,1);
    end
end

