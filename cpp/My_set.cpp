#include <iostream>
#define START_SIZE 8
using std::cout;
using std::endl;
template <typename T>
class Set {
	T *set_main;
	int size;
	int number;
	public:
		Set(T *arr=nullptr, int n=0);
		void add(T x);
		void add(T *arr, int n);
		void del(T x);
		bool in(T x) const;
		void print() const;
		void true_print();
		Set<T> operator+(const Set<T> & op) const;
		Set<T> operator*(const Set<T> & op) const;
};

template <typename T>
Set<T>::Set(T *arr, int n)
{
	size = START_SIZE;
	set_main = new T[size];
	number = 0;
	if (n) {
		int i = 0, j;
		char flag_same_element;
		for (; i < n; i++) {
			T tmp = arr[i];
			j = 0;
			flag_same_element = 0;
			while (j < number && !flag_same_element) {if (set_main[j++] == tmp) flag_same_element++;}
			if (!flag_same_element) {
				if (number == size) {
					size *= 2;
					T *set_tmp = new T[size];
					for (j = 0; j < number; j++) set_tmp[j] = set_main[j];
					delete[] set_main;
					set_main = set_tmp;
				}
				set_main[number++] = tmp;
			}
		}
	}
}

template <typename T>
void Set<T>::add(T x)
{
	int j = 0;
	char flag_same_element = 0;
	while (j < number && !flag_same_element) {if (set_main[j++] == x) flag_same_element++;}
	if (!flag_same_element) {
		if (number == size) {
			size *= 2;
			T *set_tmp = new T[size];
			for (j = 0; j < number; j++) set_tmp[j] = set_main[j];
			delete[] set_main;
			set_main = set_tmp;
		}
		set_main[number++] = x;
	}
}

template <typename T>
void Set<T>::add(T *arr, int n)
{
	int i = 0, j;
	char flag_same_element;
	for (; i < n; i++) {
		T tmp = arr[i];
		j = 0;
		flag_same_element = 0;
		while (j < number && !flag_same_element) {if (set_main[j++] == tmp) flag_same_element++;}
		if (!flag_same_element) {
			if (number == size) {
				size *= 2;
				T *set_tmp = new T[size];
				for (j = 0; j < number; j++) set_tmp[j] = set_main[j];
				delete[] set_main;
				set_main = set_tmp;
			}
		set_main[number++] = tmp;
		}
	}
}

template <typename T>
void Set<T>::del(T x)
{
	int i = 0, j = 0;
	char flag_del = 0;
	T *set_tmp = new T[size];
	for (; j < number; j++) {
		if (set_main[j] != x) set_tmp[i++] = set_main[j];
		else flag_del++;
	}
	delete[] set_main;
	set_main = set_tmp;
	if (flag_del) number--;
}

template <typename T>
bool Set<T>::in(T x) const
{	
	int j = 0;
	for (; j < number; j++) if (set_main[j] == x) return true;
	return false; 
}

template <typename T>
void Set<T>::print() const
{
	Set<T> tmp(set_main, number);
	tmp.true_print();
}

template <typename T>
void Set<T>::true_print()
{
	if (number) {
		int i = 0;
		for (; i < number; i++) {
			for (int j = 0; j < number - 1; j++) {
				if (set_main[j] > set_main[j + 1]) {
					T tmp = set_main[j];
					set_main[j] = set_main[j + 1];
					set_main[j + 1] = tmp;
				}
			}
		}
		for(i = 0; i < number - 1; i++) cout << set_main[i] << " ";
		cout << set_main[number - 1] << endl;
	} else cout << endl;
}

template <typename T>
Set<T> Set<T>::operator+(const Set<T> & op) const
{
	Set<T> obj_tmp;
	obj_tmp.add(set_main, number);
	obj_tmp.add(op.set_main, op.number);
	return obj_tmp;
}

template <typename T>
Set<T> Set<T>::operator*(const Set<T> & op) const
{
	Set<T> obj_tmp;
	int i = 0, j = 0;
	for (; i < op.number; i++) {
		for (j = 0; j < number; j++) {
			if (op.set_main[i] == set_main[j]) obj_tmp.add(set_main[j]);
		}
	} 
	return obj_tmp;
}
