#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Matrix.hpp"
#include "Rank.hpp"

using namespace std;

int main()
{
	string line;
	double size_of_matrix{ 0 }, size{ 0 }, newNumber{ 0 };
	int row{ 0 }, col{ 0 };
	
	ifstream fin;
	ofstream fout;
	fin.open("test.txt");
	if (!fin) {
		cerr << "unable to open file" << endl;
		exit(1);
	}
	//check if it's a martix in the text
	while (fin >> line) {
		++size_of_matrix;
	}
	fin.clear();
	fin.seekg(0, ios::beg);
	size = sqrt(size_of_matrix);
	Matrix a(size);
	while (fin >> line) {
		newNumber = atof(line.c_str());
		if (row < size && col == size) {
			++row;
			col = 0;
		}
		a.set_value(row, col, newNumber);
		++col;
	}
	cout << "This is matrix a:" << endl;
	cout << a << endl << endl;
	Matrix smatrix = a.importance_Matrix();
	cout << "This is matrix s:" << endl;
	cout << smatrix << endl << endl;;
	Matrix qmatrix = a.qMatrix();
	cout << "This is matrix q:" << endl;
	cout << qmatrix << endl << endl;
	Matrix mmatrix = smatrix.mMatrix(qmatrix);
	cout << "This is matrix m:" << endl;
	cout << mmatrix << endl << endl;
	cout << endl << endl << endl;
	Rank colMatrix(size);
	cout << colMatrix << endl << endl;
	colMatrix = mmatrix.markProcess(mmatrix, colMatrix);
	cout << colMatrix << endl << endl;
	Rank finalStep = mmatrix.finalStep(colMatrix);
	cout << "This is matrix pageRank:" << endl;
	cout << finalStep << endl << endl;

	fout.open( "rank.txt" );
	if (!fout) {
		cerr << "unable to open file" << endl;
		exit(1);
	}
	for (int i = 0; i < size; ++i) {
		fout << (char)(i + 65) << " = " << finalStep.arr[i] << "\n";
	}
	fout.close();


	//cout << "Matrix a(4);" << endl;
	//Matrix a(4);
	//cout << a << endl;
	//cout << "Matrix b(3);" << endl;
	//Matrix b(3);
	//cout << b << endl;
	//cout << "Matrix b, row 0, col 0 set to 13" << endl;
	//b.set_value(0, 0, 13);
	//cout << b << endl;
	//cout << "Matrix b++" << endl;
	//b++;
	//cout << b << endl;


	//int wrong_size[] = { 1, 2, 3 };
	//Matrix c(wrong_size, 3);

	//b.set_value(0, 0, -1);
	//b.set_value(0, 0, 13);
	//b.clear();

	//Matrix identity = a.identity();
	//cout << identity << endl;

	//Matrix d(2);
	//Matrix e(2);

	//if (d == e) { cout << "equal" << endl; }
	//if (d >= e) { cout << "c is greater than d" << endl; }

	//Matrix f = d + e;
	//cout << "F: \n" << f << endl; //error

	//d += a;

	//cout << "D: \n" << d << endl; //error

	system("pause");
	return 0;
}
