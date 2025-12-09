#include <iostream>
#include <vector>
#include <string>
using namespace std;


void selectionSort(vector<string>& arr){
    int n = arr.size();
    for (int i=0; i<n; i++){
        int min = i;
        for (int j=i; j<n; j++){
            if (arr[j] <= arr[min]){
                min = j;
            }
        }
        string temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    vector<string> arr = {"banana", "apple", "cherry", "date",};
    
    selectionSort(arr);
    
    cout << "Sorted array: ";
    for (const string& str : arr) {
        cout << str << " ";
    }
    cout << endl;
    
    return 0;
}
