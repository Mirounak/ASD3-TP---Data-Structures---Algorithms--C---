#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main() {
    int n = 1000;
    auto start = high_resolution_clock::now();
    

    for (int i=1 ;i<n ;i*=2){
        cout << i << endl;
    }
    
  
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt", ios::app);
    output << "Execution time of logarithmic with input = " << n << " : "<< duration << " microseconds" << endl;

    return 0;
}