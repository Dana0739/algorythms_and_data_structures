#include <fstream>
#include <iostream>

using namespace std;

int main() {
    ifstream input ("input.txt");
    ofstream output ("output.txt");

    int n;
    input >> n;
    int half = n / 2;
    int* heap = new int[n + 1];

    for (int i = 1; i <= n; i++) {
        input >> heap[i];
    }

    for (int i = 1; i < half; i++) {
        if (!(heap[i] <= heap[i * 2] && heap[i] <= heap[i * 2 + 1])) {
            output << "NO";
            return 0;
        }
    }

    output << "YES";
    return 0;
}