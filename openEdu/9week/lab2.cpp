#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	ifstream input("input.txt");
	ofstream output("output.txt");

	string str = "";
	string tmp;
	map<char, vector<long>> letters_ids;
	long long temp;
	long long sum;
	long long x = 0;
	long k;

	getline(input, str);
	str.erase(remove(str.begin(), str.end(), ' '), str.end());

	for (long i = 0; i < str.size(); i++) {
		letters_ids[str[i]].push_back(i);
	}

	for (char i = 'a'; i <= 'z'; i++) {
		if (letters_ids.count(i) && letters_ids[i].size() > 1) {
			sum = 0;
			k = letters_ids[i].size() - 1;
			for (long j = letters_ids[i].size() - 1; j >= 0; j--) {
				temp = (long long)k * letters_ids[i][j];
				sum += temp;
				k -= 2;
			}
			for (long j = 1; j < letters_ids[i].size(); j++)
			{
				sum -= j;
			}

			x += sum;
		}
	}

	output << x;
	return 0;
}