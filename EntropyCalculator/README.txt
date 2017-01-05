Joseph Phan
Lab Section : Fri 2:15
Lab 5


--------------- About ---------------

The Entropy Calculator that takes in any file type that will produce
an Entropy Value. The algorithm to find a file's entropy involves creating a 
frequency array for every corresponding byte. After this the program iterates
through the frequency array, creates a probability distribution, and then sums
this up to find the entropy.

The random text file generator that created a random text file 
given the number of byes wanted. For every byte, it used C's rand() function
to select one character from teh ASCII table random and added that to the
random byte stream.


--------------- Arguments ---------------
randgenerator.c
 - 2 command line inputs
 - First input: # bytes for random stream of symbols
 - Second input: name of text file writing too

entropyCalculator.c
 - 1 command line input
 - First input: name of text file produced by randgenerator.c



------------ Using My MakeFile -----------
to test and get the results as show above just type to command line "make"
to remove all the input files, type in "make clean"



--------------- Results ---------------
---Testing my files ---
on a "Hello World" txt  ---------------------- 3.022055
on a star image ------------------------------ 7.853734
on a romeo & juliet pdf ---------------------- 7.553099
on a compressed star image ------------------- 7.973442
on a compressed romeo & juliet pdf ----------- 7.998674

--- Testing Different Random File Sizes ---
on a 100 byte random txt --------------------- 6.288758
on a 1000 byte random txt -------------------- 7.812065
on a 10000 byte random txt ------------------- 7.984511
on a 100000 byte random txt ------------------ 7.998044
on a 1000000 byte random txt ----------------- 7.999835



------------ Result Analysis ------------
The compressed files had a higher entropy because even though it shrinks a file,
it has a higher entropy density per length of the file.
The reason why Hello World text was so small was because of its small size. The 
larger the file size, the more likely it will have a higher entropy. We can
see this from the results from testing different File sizes. I tested from
100 bytes to 1 megabyte going in orders of 10. By the time the file size was 
at 1b it was almost at the highest entropy of 8. 


