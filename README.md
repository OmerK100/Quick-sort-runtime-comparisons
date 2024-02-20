C program that compares run-times of different Quick-Sort algorithm versions by counting number of comparisons
made upon permutations from 1 to n, when n is chosen by the user (the larger n is the more permutations there are and the calculations are heavier, be noted!)
and the run-times calculated are best, average and worst cases. The division into different cases is made using the quick-select algorithm which runs in linear O(n) time
and finds the number that belongs to index i of the array, when the array is sorted.

The first quick-sort we compare is the classic version, which seperates the array using a pivot, the pivot is chosen as the last number in the array.
The second version of quick-sort is the best-pivotted algorithm which chooses a pivot in the array that will seperate the array in half. 
The seperation into two equal parts is supposed to make the algorithm run quciker but the search for the best pivot within the array is quite expensive by efficiency means.
![image](https://github.com/OmerK100/RandomStuff/assets/139342166/04382e90-29a5-43bd-af8d-76f0a12c22dd)
