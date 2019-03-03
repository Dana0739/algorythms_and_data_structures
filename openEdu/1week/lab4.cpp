#include <iostream>
#include <fstream>
#include <vector>
//#include <iterator>
#include <map>
using namespace std;

int main()
{
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	int n;
	float curValue;
	vector<float> moneyList;
	map<float, int> moneyToIndex;
	infile >> n;
	for (int i = 0; i < n; i++) {
		infile >> curValue;
		moneyList.push_back(curValue); // добавляем в список новые элементы
		moneyToIndex[curValue] = i + 1; // добавляем элементы в словарь: (значение элемента -> его индекс в исходном файле)
	}
	infile.close();

	// сортировка вставками
	for (int i = 1; i < n; i++) {
		int j = i - 1;
		while (j >= 0 && moneyList[j] > moneyList[j + 1]) {
			curValue = moneyList[j];
			moneyList[j] = moneyList[j + 1];
			moneyList[j + 1] = curValue;
			j--;
		}
	} // вывод индексов первого, среднего и последнего элементов отсортированного массива через словарь
	outfile << moneyToIndex[moneyList[0]] << " " <<
		moneyToIndex[moneyList[(n - 1) / 2]] << " " <<
		moneyToIndex[moneyList[n - 1]];
	outfile.close();
	
	/*
	map <float, int> :: iterator it = moneyToIndex.begin();
	outfile << it->second << " ";
	advance(it, (n - 1) / 2);
	outfile << it->second << " ";
	advance(it, (n - 1) / 2);
	outfile << it->second;
	outfile.close();

	почему-то автоматическая сортировка map на большом количестве элементов (5861) не работает, вероятно это немного оптимальнее
	а так это была бы очень хитрая оптимизация)
	*/

	return 0;
}