#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");


	string substr, str;
	vector<int> entries_ids;

	getline(input, substr);
	getline(input, str);

	for (unsigned it = 0; it != str.size(); ++it) {
		if (str[it] == substr[0]) {
			entries_ids.push_back(it + 1);
			for (unsigned sub_it = 0; sub_it != substr.size(); ++sub_it) {
				if (str[it + sub_it] != substr[sub_it]) {
					entries_ids.pop_back();
					break;
				}
			}
		}
	}

	output << entries_ids.size() << '\n';

	for (unsigned i = 0; i < entries_ids.size(); i++) {
		output << entries_ids[i] << " ";
	}
}
