#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int largest_sum(int nums[], int l, int r) {
    int mid = (l+r)/2;
    int sum = 0;
    int sum_l = INT_MIN;
    int sum_r = INT_MIN;
    
    if (l-r == 0)
        return nums[l];

    for (int i=mid; i>=l; i--) {
        sum += nums[i];
        if (sum > sum_l)
            sum_l = sum;
    }
    sum = 0;
    for (int i=mid+1; i<=r; i++) {
        sum += nums[i];
        if (sum > sum_r)
            sum_r = sum;
    }

    return max(max(largest_sum(nums, l, mid), largest_sum(nums, mid+1, r)), sum_l+sum_r);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Please input array of integers.\n";
        return 0;
    }
    
    int* data  = (int*)calloc( argc-1, sizeof(int));
    for (int i = 0; i < argc-1; i++) {
        // convert string to an integer
        sscanf( argv[i + 1], "%d", &data[i] ) ;
    }

    cout << "The largest sum of consecutive integers in the array is " << largest_sum(data, 0, argc-2) << ".\n";
    return 0;
}
