# Divide and Conquer

## Usage
To build the program, move into the `src` folder and run `make`. This will build two applications: largest_sum and city_skyline.

`./city_skyline <num_buildings>` allows the user to run the "City Skyline" algorithm with the specified number of randomly generated buildings as input.

`./largest_sum <value_1> <value_2> … <value_3>` allows the user to run the "Largest Consecutive Sum" algorithm with the specified integer array as input.


### City Skyline
Find the city skyline provided a list of building coordinates.

##### Algorithm Description:

In order to generate a city skyline, provided a list of building coordinates sorted in increasing order by their leftmost x-coordinate, in O(n log(n)), a divide and conquer approach can be used. A recursive function divides the array of buildings into two parts of half the size until the array is of size one. Once the array is size one, a skyline can easily be generated for the building (l, h, r) as [(1,0), (l,h), (r,100)]. These skylines can then be merged together as the recursion retraces backward, much like in the merge sort algorithm. To merge two skylines together, the two arrays of skyline segments are iterated over and the segment with the minimum left x-coordinate is removed from its skyline and a segment is potentially added to a resultant skyline. The new segment is added to the merged skyline if the segment removed has a height greater than the last skyline segment in the list. If the last segment in the merged skyline has the same starting point as the new segmenta and the new potential segment has a greater height, it takes the place of the last skyline segment, otherwise the new segment is discarded.

##### CPU Time for Simulated Trials:

Running three trials for five increasingly large input quantities, the average CPU time to find the city skyline for datasets of each size was found. The trend, as seen on the table and graph below, illustrates the O(n log(n)) runtime for this algorithm. The graph plots our average CPU time to complete the algorithm for each size input alongside the graph of n log(n) multiplied by a constant factor (10^-4).

![runtime table](https://github.com/tamargoadam/divide-and-conquer/blob/main/imgs/city_skyline_complexity_table.png)

![complexity graph](https://github.com/tamargoadam/divide-and-conquer/blob/main/imgs/city_skyline_complexity_graph.png)

### Largest Consecutive Sum
Find the largest possible sum of sub-sequence of consecutive items in a list.

##### Algorithm Description:

In order to find the largest sum on consecutive integers in an array of positive and negative integers, we can take a recursive approach. To do this we must consider three possibilities: the largest consecutive sum is in the left half of the array, is in the right half of the array, or is spanning the midpoint of the array.
The base case for the recursive function is where the array is only one integer long; in this case, the integer’s value is returned. If the array has a length greater than one, return the maximum of the previously stated three possibilities. Finding the largest sum in the left and right halves of the array is simply done by recursively calling the function for the respective halves. Iterating from the midpoint to the leftmost or rightmost index and setting a sum value (initially set to negative infinity) equal to the sum of all the values encountered if it is greater than the current sum and then summing those two values for the left and right will find the maximum sum of integers potentially spanning the midpoint of the array.

##### Proof of Correctness:

For this problem, a proof by induction is appropriate:
- The base case will be that an array of size 1 will always return the largest sum of consecutive elements. This is obviously true because there is only one consecutive element, so it itself must be the largest sum, and, as described in the algorithm above, the base case for the recursive function covers this case.
- For the inductive step, assume that all array sizes less than n can be solved with this algorithm.
- Now the three possible cases for a solution on the array A of size n need to be considered. Let L be the array of integers from the first index in A to the midpoint and let R be the array of integers from the midpoint+1 to the last index in A. The three possibilities for a solution are as follows:
  - The solution lies in L 
  - The solution lies in R
  - The solution spans the midpoint of A
- Since it has been stated that all solutions for arrays of size less than n can be solved and both L and R are of size less than n, the first two cases are covered trivially.
- The case in which we need to find the largest sum spanning the midpoint we can confirm that the result is correct because all possible sums are checked for subsequences starting from the rightmost index of L and the leftmost index of R. Since every possibility is checked the left sum and right sum must be correct. 
- Summing two values for the greatest sum of consecutive integers left from the midpoint and the greatest sum of consecutive integers right from the midpoint must provide the greatest sum of integers spanning the midpoint.
- Since all three calculations are proven to provide correct results, the maximum of the three must be the largest sum of consecutive integers for the whole array.

##### Proof of Order Notation:

The worst case time complexity of this algorithm is O(n log(n)). We can prove this via induction:
- First, note that the time to run this algorithm on an input of size n, T(n) = T(n/2) + T(n/2) + n. The two T(n/2) come from the two recursive calls with input of size n/2 and the additional n comes from the need to traverse every element in the input array to check if a spanning subsequence has the largest consecutive sum.
- The base case for this is T(1) = 0.
- The inductive hypothesis states that T(n) = n log(n).
```
T(2n) = T(n) + T(n) + 2n
= 2T(n) + 2n
= 2n log(n) + 2n	(using our assumption that T(n) = n log(n))
= 2n (log(2n) - 1) + 2n
= 2n log(2n)
```
- Thus T(n) = n log(n) and the algorithm is O(n log(n)).
