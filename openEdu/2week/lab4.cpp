#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    size_t n;
    unsigned k1, k2;
    int A, B, C, temp;
    input >> n >> k1 >> k2;
    k1--;
    k2--;
    input >> A >> B >> C;
    vector<int> values;

    values.reserve(n);
    input >> temp;
    values.push_back(temp);
    input >> temp;
    values.push_back(temp);

    for (size_t i = 2; i < n; ++i) {
        values.push_back(A * values[i - 2] + B * values[i - 1] + C);
    }

    nth_element(values.begin(), values.begin() + k1, values.end());
    nth_element(values.begin(), values.begin() + k2, values.end());
    sort(values.begin() + k1, values.begin() + k2);

    for (unsigned i = k1; i <= k2; i++) {
        output << values[i] << " ";
    }
}
