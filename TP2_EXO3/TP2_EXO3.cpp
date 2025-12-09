#include <iostream>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void hanoi(int n, char from, char aux, char to) {
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to << endl;
        return;
    }
    hanoi(n - 1, from, to, aux);
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    hanoi(n - 1, aux, from, to);
}

int main() {

    int n = 3; 

    auto start = high_resolution_clock::now();
    hanoi(n, 'A', 'B', 'C');
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    ofstream output("output.txt", ios::app);
    output << "Execution time of Tower of Hanoi with n = " << n << " : " << duration << " microseconds" << endl;
    cout << "Hanoi timing appended to output.txt (n=" << n << ")" << endl;
    return 0;
}
