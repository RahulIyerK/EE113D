#!/bin/bash
rm -rf ./preprocessed_data
mkdir preprocessed_data

for vowel in "aah" "ee" "eh" "oo"
do
	for i in {1..10}
	do
		filename="${vowel}_mfcc"
		tail -n +2 "${filename}_${i}.dat" >> ./preprocessed_data/"${filename}.dat"
	done
done


