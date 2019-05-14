#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    string s;
    input >> s;
    int L = 0, R = 0;
    int j = 0;
    int *z = new int[s.size() + 1];

    for (int i = 1; i < s.size(); i++) {
        if (i >= R) {
            j = 0;
            while (i + j < s.size() && s[i + j] == s[j]) {
                j++;
            }
            L = i;
            R = i + j;
            z[i] = j;
        } else {
            if (z[i - L] < R - i) {
                z[i] = z[i - L];
            } else {
                j = R - i;
                while (i + j < s.size() && s[i + j] == s[j]) {
                    j++;
                }
                L = i;
                R = i + j;
                z[i] = j;
            }
        }
    }

    for (size_t c = 1; c < s.size(); c++) {
        output << z[c] << ' ';
    }
}