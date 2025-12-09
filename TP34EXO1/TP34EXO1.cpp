#include <iostream>
using namespace std;

void interpolationSearch(int arr[], int n, int key) {
    
    if (n <= 0) {
        return;
    }

    int high = n - 1;
    int low = 0;

    
    while (key >= arr[low] && key <= arr[high] && low <= high) {

        int pos = low + (high - low) * (key - arr[low]) /
                    (arr[high] - arr[low]);
        
        cout << "Probing at index: " << pos << endl;
        if (arr[pos] == key) {
            cout << "Element found at index: " << pos << endl;
            return;
        } else if (arr[pos] < key) {
            low = pos + 1; 
        } else { 
            high = pos - 1; 
        }
    }

    return; 
}


int main() {

    int array[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};


    int size = sizeof(array) / sizeof(array[0]);

    int target_value = 256;
    
    
    interpolationSearch(array, size, target_value);

    
    return 0;
}