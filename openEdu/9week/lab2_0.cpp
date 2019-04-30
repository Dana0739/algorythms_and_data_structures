#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	string str, alphabet;
	alphabet = "abcdefghijklmnopqrstuvwxyz";
	unsigned x = 0;

	getline(input, str);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	for (size_t i = 0; i < alphabet.size(); i++) {
		vector<int> entries_ids;
		char substr = alphabet[i];
		for (unsigned it = 0; it != str.size(); ++it) {
			if (str[it] == substr) {
				entries_ids.push_back(it);
				if (entries_ids.size() != 1) {
					for (unsigned j = 0; j < entries_ids.size() - 1; j++) {
						x += it - entries_ids[j] - 1;
					}
				}
			}
		}
	}
	
	output << x;
}
