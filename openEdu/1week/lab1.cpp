#include <iostream>
#include <fstream>

int main()
{
	std::ifstream infile("input.txt");
	std::ofstream outfile("output.txt");
	int a, b;
	infile >> a >> b;
	infile.close();
	outfile << (a + b);
	outfile.close();
	return 0;
}