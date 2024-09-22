#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using std::cout;
using std::vector;
using std::endl;
using std::stoi;
class Matrix
{
	vector <int> v;
	int row_i, column_j;
	enum pos{BEFORE=1, AFTER=2};
	public:
		Matrix(int x, int y);
		void transpose();
		void insert_row(int num, char pos);
		void insert_column(int num, char pos);
		void delete_row(int num);
		void delete_column(int num);
		void swap_rows(int num1, int num2);
		void swap_columns(int num1, int num2);
		void print() const;
};

Matrix::Matrix(int x, int y)
{
	int tmp;
	row_i = x;
	column_j = y;
	for(int i=0; i < x * y; i++) {
		scanf("%d", &tmp);
		v.push_back(tmp);
	}
}

void Matrix::transpose()
{
	vector <int> tmp;
	for (int j=0; j < column_j; j++) for (int i=0; i < row_i; i++) tmp.push_back(v[i * column_j + j]);
	v = tmp;
	int x = row_i;
	row_i = column_j;
	column_j = x;
}

void Matrix::insert_row(int num, char pos)
{	
	if (num > 0 && num <= row_i)
	{
		if (pos == BEFORE) num--;
		int x;
		for(int j=0; j < column_j; j++)
		{
			scanf("%d", &x);
			v.insert(v.begin() + num * column_j + j, x);
		}
		row_i++;
	}
}

void Matrix::insert_column(int num, char pos)
{	
	if (num > 0 && num <= column_j)
	{
		if (pos == BEFORE) num--;
		int x;
		for(int i=0; i < row_i; i++)
		{
			scanf("%d", &x);
			v.insert(v.begin() + num + i * column_j + i, x);
		}
		column_j++;
	}
}

void Matrix::delete_row(int num)
{
	if (num > 0 && num <= row_i)
	{
		num--;
		for(int j=0; j < column_j; j++) v.erase(v.begin() + num * column_j);
		row_i--;
	}
}

void Matrix::delete_column(int num)
{
	if (num > 0 && num <= column_j)
	{
		num--;
		for(int i=row_i-1; i >= 0; i--) v.erase(v.begin() + num + column_j * i);
		column_j--;
	}
}

void Matrix::swap_rows(int num1, int num2)
{
	if (num1 > 0 && num1 <= row_i && num2 > 0 && num2 <= row_i && (num1 != num2)) {
		int tmp;
		num1--;
		num2--;
		for(int j=0; j < column_j; j++)
		{
			tmp = v[num1 * column_j + j];
			v[num1 * column_j + j] = v[num2 * column_j + j];
			v[num2 * column_j + j] = tmp;
		}
	}
}

void Matrix::swap_columns(int num1, int num2)
{
	if (num1 > 0 && num1 <= column_j && num2 > 0 && num2 <= column_j && (num1 != num2)) {
		int tmp;
		num1--;
		num2--;
		for(int i=0; i < row_i; i++)
		{
			tmp = v[num2 + column_j * i];
			v[num2 + column_j * i] = v[num1 + column_j * i];
			v[num1 + column_j * i] = tmp;
		}
	}
}

void Matrix::print() const
{
	for(int i=0; i < row_i; i++) {
		for(int j=0; j < column_j; j++)
		{
			cout << v[column_j * i + j] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	int x, y;
	scanf("%d", &x);
	scanf("%d", &y);
	Matrix matrix(x, y);
	int num1, num2;
	if (argc >= 3) num1 = stoi(argv[2]);
	if (argc == 4) num2 = stoi(argv[3]);
	switch(argc)
	{
		case 2:
			if (!strcmp(argv[1], "-t")) matrix.transpose();
			break;
		case 3:
			enum pos{BEFORE=1, AFTER=2};
			if (!strcmp(argv[1], "-irb")) matrix.insert_row(num1, BEFORE);
			else if (!strcmp(argv[1], "-ira")) matrix.insert_row(num1, AFTER);
			else if (!strcmp(argv[1], "-icb")) matrix.insert_column(num1, BEFORE);
			else if (!strcmp(argv[1], "-ica")) matrix.insert_column(num1, AFTER);
			else if (!strcmp(argv[1], "-dr")) matrix.delete_row(num1);
			else if (!strcmp(argv[1], "-dc")) matrix.delete_column(num1);
			break;
		case 4:
			if (!strcmp(argv[1], "-sr")) matrix.swap_rows(num1, num2);
			else if (!strcmp(argv[1], "-sc")) matrix.swap_columns(num1, num2);
			break;
	}
	matrix.print();
	return 0;
}
