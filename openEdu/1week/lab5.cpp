#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	int n, curValue;
	vector<int> arrayList;
	infile >> n;
	for (int i = 0; i < n; i++) {
		infile >> curValue;
		arrayList.push_back(curValue); // добавляем в список новые элементы
	}
	infile.close();
	// сортировка перестановками
	for (int i = 0; i < n - 1; ++i) {
		int min_index = i;
		for (int j = i + 1; j < n; ++j) {
			if (arrayList[min_index] > arrayList[j]) { // ищем минимальное число в срезе массива от текущего индекса до конца
				min_index = j;
			}
		}
		if (i != min_index) { // минимальный элемент в срезе должен оказаться по текущему индексу. он или уже там, или делаем перестановку
			curValue = arrayList[i];
			arrayList[i] = arrayList[min_index];
			arrayList[min_index] = curValue;
			outfile << "Swap elements at indices " << i + 1 << " and " << min_index + 1 << "." << endl; // ыводим перестановку
		}
	}
	outfile << "No more swaps needed.";
	outfile << endl;
	for (int i = 0; i < n - 1; i++) {
		outfile << arrayList[i] << " ";
	}
	outfile << arrayList[n - 1];
	outfile.close();
	return 0;
}