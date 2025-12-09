#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1; 
    while (low <= high) { 
        int mid = low + (high - low) / 2; 
        if (arr[mid] == target)
            return mid; 
        else if (arr[mid] < target) 
            low = mid + 1; 
        else
            high = mid - 1; 
    }
    return -1; 
}

int main() {
    int n = 10;
    auto start = high_resolution_clock::now();

    int arr[] = {1, 2, 3, 4, 5};
    int target = 5;
    int result = binarySearch(arr, 5, target);

    cout << "Element found at index: " << result << endl;

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt", ios::app);
    output << "Execution time of binary search with inpute = " << n << " : "<< duration << " microseconds" << endl;

    return 0;
}