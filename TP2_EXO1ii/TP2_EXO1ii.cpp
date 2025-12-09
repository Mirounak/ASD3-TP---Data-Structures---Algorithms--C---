#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main() {
    int n = 10;
    auto start = high_resolution_clock::now();
    
    for (int i=0 ;i<n ;i++){
        for (int j=0;j<n ;j++){

            cout << i + j << endl;
        }
    }
    
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt", ios::app);
        output << "Execution time of quadratic with inpute = " << n << " : "<< duration << " microseconds" << endl;


    return 0;
}