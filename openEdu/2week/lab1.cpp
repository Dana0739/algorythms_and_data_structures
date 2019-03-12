#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void merge(int *arr, int l1, int r1, int l2, int r2) {
	vector<int> newArr;
	int k = l1;
	while (l1 < r1 || l2 < r2) {
		if (l2 == r2 || (l1 < r1 && arr[l1] <= arr[l2])) {
			newArr.push_back(arr[l1]);
			l1++;
		}
		else {
			newArr.push_back(arr[l2]);
			l2++;
		}
	}
	for (int c = k; c < r2; ++c) {
		arr[c] = newArr[c - k];
	}
}

void sort(int *arr, int L, int R, int *output) {
	if (L == R) {
		return;
	}
	int newR1 = L + (R - L) / 2;
	sort(&arr[0], L, newR1, &output[0]);
	int newL2 = newR1 + 1;
	sort(&arr[0], newL2, R, &output[0]);
	merge(&arr[0], L - 1, newR1, newL2 - 1, R);
	int k = 4 * output[0];
	output[k + 1] = L;
	output[k + 2] = R;
	output[k + 3] = arr[L - 1];
	output[k + 4] = arr[R - 1];
	output[0] = k / 4 + 1;
}

int main()
{
	ifstream infile("input.txt");
	int n, curValue;
	vector<int> arrayList, output;
	infile >> n;
	for (int i = 0; i < n; i++) {
		infile >> curValue;
		arrayList.push_back(curValue); // добавляем в список новые элементы
		output.push_back(0);
		output.push_back(0);
		output.push_back(0);
		output.push_back(0);
	}
	infile.close();

	sort(&arrayList[0], 1, n, &output[0]);

	ofstream outfile("output.txt");
	
	for (int i = 0; i < output[0]; i++) {
		outfile << output[i * 4 + 1] << " ";
		outfile << output[i * 4 + 2] << " ";
		outfile << output[i * 4 + 3] << " ";
		outfile << output[i * 4 + 4];
		outfile << endl;
	}

	// выводим в файл результирующий массив
	for (int i = 0; i < n - 1; i++) {
		outfile << arrayList[i] << " ";
	}
	outfile << arrayList[n - 1];
	outfile.close();
	return 0;
}
