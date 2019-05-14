#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string s;
    input >> s;
    int *p = new int[s.size() + 1];
    int i = 1, j = 0;
    while (i < s.size()) {
        if (s[i] == s[j]) {
            p[++i] = ++j;
        } else {
            if (j > 0) {
                j = p[j];
            } else {
                p[++i] = 0;
            }
        }
    }

    for (size_t c = 1; c <= s.size(); c++) {
        output << p[c] << ' ';
    }
}
