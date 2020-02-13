clear all;

aah_mfcc = load("aah_mfcc.dat");
aah_mfcc = reshape(aah_mfcc, [13,10]);
aah_mfcc = aah_mfcc';

ee_mfcc = load("ee_mfcc.dat");
ee_mfcc = reshape(ee_mfcc, [13,10]);
ee_mfcc = ee_mfcc';

eh_mfcc = load("eh_mfcc.dat");
eh_mfcc = reshape(eh_mfcc, [13,10]);
eh_mfcc = eh_mfcc';

oo_mfcc = load("oo_mfcc.dat");
oo_mfcc = reshape(oo_mfcc, [13,10]);
oo_mfcc = oo_mfcc';

input = vertcat(aah_mfcc, eh_mfcc, ee_mfcc, oo_mfcc);

output = zeros(40,4);
output(1:10,:) = repmat([1,0,0,0],10,1);
output(11:20,:) = repmat([0,1,0,0],10,1);
output(21:30,:) = repmat([0,0,1,0],10,1);
output(31:40,:) = repmat([0,0,0,1],10,1);