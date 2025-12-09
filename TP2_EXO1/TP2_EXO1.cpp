#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

int main() {
    int n = 1000;
    auto start = high_resolution_clock::now();
    
    for (int i=0 ;i<n ;i++){
        cout << i << endl;
    }
   
 
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt");
       output << "Execution time of linear with inpute = " << n << " : "<< duration << " microseconds" << endl;


    return 0;
}