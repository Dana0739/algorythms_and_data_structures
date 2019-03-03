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
	vector<int> indexList;
	infile >> n;
	for (int i = 0; i < n; i++) {
		infile >> curValue;
		arrayList.push_back(curValue); // добавляем в список новые элементы
	}
	infile.close();
	indexList.push_back(1);
	for (int i = 1; i < n; i++) { //сортируем методом вставок
		int j = i - 1;
		while (j >= 0 && arrayList[j] > arrayList[j + 1]) {
			curValue = arrayList[j];
			arrayList[j] = arrayList[j + 1];
			arrayList[j + 1] = curValue;
			j--;
		}
		indexList.push_back(j + 2);
	}
	for (int i = 0; i < n - 1; i++) {
		outfile << indexList[i] << " "; //вывод индексов
	}
	outfile << indexList[n - 1];
	outfile << endl;
	for (int i = 0; i < n - 1; i++) {
		outfile << arrayList[i] << " "; //вывод массива результа
	}
	outfile << arrayList[n - 1];
	outfile.close();
	return 0;
}