#!/bin/bash

alphabet_sizes=(2 4 20 70)
word_lengths=(4 5 6 7 8 9 10 15 20 30 40 50)
word_count=100
alphabet_file="alphabet.txt"
output_dir="gen"


mkdir -p "$output_dir"

make generator || exit 1

for alphabet_size in "${alphabet_sizes[@]}"; do
  mkdir -p ./gen/"alph-$alphabet_size"
  ./generator -m g -a "$alphabet_size" | tee ./gen/"alph-$alphabet_size"/$alphabet_file

  ./generator -m t -a "$alphabet_size" -l 500000 -i ./gen/"alph-$alphabet_size"/$alphabet_file > ./gen/"alph-$alphabet_size"/text.txt
  
   for word_length in "${word_lengths[@]}"; do
     output_file="${output_dir}/"alph-$alphabet_size"/wordlist_alph-${alphabet_size}-wordlength_${word_length}.txt"

     ./generator -m w -a "$alphabet_size" -l "$word_length" -n "$word_count" -i ./gen/"alph-$alphabet_size"/$alphabet_file > "$output_file"

     echo "Generated file: $output_file"
   done
done

echo "All files are generated in the following directory: '$output_dir'."
