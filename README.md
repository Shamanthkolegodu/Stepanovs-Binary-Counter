# Stepanovs-Binary-Counter

Implementation of Stepanov’s Binary counter to find the second largest element in an array of distinct/unique integers.

# Problem statement

Implement Stepanov’s Binary counter to find the second largest element in an array of distinct/unique integers. Let n be the number of elements in the array (n>=2). n may or may not be an exact power of 2.The algorithm should have at most "n + logn - 2" comparisons (however when n is not an exact power of 2, the number of comparisons can be little more). It may use extra space proportional to (logn) ^ 2.

# Function to be implemented

- void find_second_greatest(int \*numbers, int length)
  The function should give the output in the given format (check the screenshots). No deviations from the format are allowed. If the output is not according to the required format, you will be awarded 0 for this assignment.
  The initial lines represent a match being played between the numbers on the LHS and the result of that match is on the RHS of the = sign. Each line except the last two lines represent the match played and it’s result. The last line is the second largest integer in the array.

The output set will first have the highest of all elements of the two sets.
This will be followed by the highest number in the losing set.
Finally, the numbers that have lost to the largest number from the winning set are printed.

Consider:
25 20 15 x 18 10 2 = 25 18 20 15  
Here, the two competing sets are 25 20 15 and 18 10 2.
25 20 15 is the winning set, and 18 10 2 is the losing set.
The largest number of the two sets is 25, and hence is printed first, post the '=' sign.

The largest number of the losing set is 18, and hence is printed as the second number.
This is followed by all the numbers that have lost to 25(ie, 20 15), in the same order as in the winning set.

# Data structures used: Adjacency List

# How to compile your code:
Compile using: gcc -Wall main.c client.c -o program
Then run using: ./program

## Fine techniques course @PES University.
