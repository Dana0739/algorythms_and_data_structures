#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> fillAntiQuick(size_t n) {
    vector<int> values;
    values.reserve(n);
    if (n < 2) {
        return {1};
    }
    values.push_back(1);
    values.push_back(2);
    int i = 3;
    while (values.size() != n) {
        values.push_back(i);
        swap(values[i - 1], values[(i - 1) / 2]);
        i++;
    }
    return values;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    size_t n;
    input >> n;

    for (auto& i : fillAntiQuick(n)) {
        output << i << " ";
    }
}