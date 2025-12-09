#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int left, int mid, int right) {
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    int leftArray[sizeLeft], rightArray[sizeRight];

    for (int i = 0; i < sizeLeft; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < sizeRight; j++)
        rightArray[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < sizeLeft && j < sizeRight) {
        if (leftArray[i] <= rightArray[j])
            arr[k++] = leftArray[i++];
        else
            arr[k++] = rightArray[j++];
    }
    while (i < sizeLeft) arr[k++] = leftArray[i++];
    while (j < sizeRight) arr[k++] = rightArray[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int n = 10000;
    int arr[n];
    
   
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }

    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt", ios::app);
    output << "Execution time of merge sort with n = " << n << " : " << duration << " microseconds" << endl;
    output.close();

    return 0;
}
