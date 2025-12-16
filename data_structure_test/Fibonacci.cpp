#include <iostream>
using namespace std;

// Function to generate Fibonacci sequence up to n terms
void generateFibonacci(int n) {
    int t1 = 0, t2 = 1, nextTerm;

    cout << "Fibonacci Sequence: ";

    for (int i = 1; i <= n; ++i) {
        cout << t1 << " ";
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
    cout << endl;
}

int main() {
    int n;

    cout << "Enter the number of terms: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
    } else {
        generateFibonacci(n);
    }

    return 0;
}