#include <iostream>
using namespace std;

void pm(int start, int end) {
    cout << start << " -> " << end << endl;
}

void h(int n, int start, int end, int other) {
    if (n == 1) {
        pm(start, end); //base case
    } else {
        h(n - 1, start, other, end);
        pm(start, end);
        h(n - 1, other, end, start);
    }
}

int main() {
    cout << "enter number of disks: ";
    int n;
    cin >> n;
    cout << "which tower to move from (1, 2, or 3): ";
    int start;
    cin >> start;
    cout << "which tower to move to (1, 2, or 3): ";
    int end;
    cin >> end;
    cout << "which tower is the auxilairy (1, 2, or 3): ";
    int other;
    cin >> other;
    cout << "Moves:" << endl;
    h(n, start, end , other);
    return 0;
}


