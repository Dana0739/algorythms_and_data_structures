#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

void merge(vector<int>& values, size_t first_part, size_t first_size, size_t second_part, size_t second_size,
        size_t& inversions) {
    size_t i = 0, j = 0;
    vector<int> first{values.begin() + first_part, values.begin() + first_part + first_size};
    vector<int> second{values.begin() + second_part, values.begin() + second_part + second_size};
    size_t current_pos = first_part;
    while (i < first.size() || j < second.size()) {
        if (j == second.size() || (i < first.size() && first[i] <= second[j])) {
            values[current_pos++] = first[i++];
            inversions += j;
        } else {
            values[current_pos++] = second[j++];
        }
    }
}

void sort(vector<int>& values, size_t L, size_t R, size_t& inversions) {
    size_t size = R - L;
    if (size == 1) {
        return;
    }
    sort(values, L, L + size / 2, inversions);
    sort(values, L + size / 2, R, inversions);
    merge(values, L, size / 2, L + size / 2, size / 2 + size % 2, inversions);
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    size_t n;
    input >> n;
    vector<int> values(n);
    size_t inversions = 0;

    for (size_t i = 0; i < n; i++) {
        input >> values[i];
    }

    sort(values, 0, values.size(), inversions);

    output << inversions;
}