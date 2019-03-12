#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node{
    int value;
    size_t start_index;

    bool operator< (const Node& rhs) {
        return value < rhs.value;
    }
};

bool checkSides(vector<Node>& values, size_t index) {
    if (index != 0 && index != values.size() - 1)
        return values[index].value == values[index + 1].value || values[index].value == values[index - 1].value;
    if (index == 0 && values.size() == 1)
        return false;
    if (index == 0)
        return values[index].value == values[index + 1].value;
    return values[index].value == values[index - 1].value;
}

bool Detect(vector<Node>& values, size_t step) {
    sort(values.begin(), values.end());
    for (size_t i = 0; i < values.size(); i++) {
        if ((max(i, values[i].start_index) - min(i, values[i].start_index)) % step != 0) {
            if ((step == 2 || step == 50000) && checkSides(values, i)) {
                continue;
            }
            return false;
        }
    }
    return true;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    size_t n, k;
    input >> n >> k;

    vector<Node> values;
    values.reserve(n);
    int temp;

    for (size_t i = 0; i < n; i++) {
        input >> temp;
        values.push_back({temp, i});
    }

    if (Detect(values, k)) {
        output << "YES";
    } else {
        output << "NO";
    }
}