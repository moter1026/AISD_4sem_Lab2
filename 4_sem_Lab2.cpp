// 4_sem_Lab2.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include <unordered_map>

#include "4_sem_Lab2.h"

using namespace std;

int main()
{
	My_unordered_map<int> My_class(15);

	My_class.ptint();

	My_class.insert(124, 1000);
	My_class.insert(555, 2000);
	My_class.insert(333, 3000);
	My_class.insert(111, 4000);
	My_class.insert(111, 5000);
	My_class.insert(111, 6000);
	My_class.insert(124, 7000);
	My_class.insert(124, 8000);
	My_class.insert(124, 9000);
	My_class.insert(124, 10000);
	My_class.insert(124, 11000);
	My_class.insert(555, 12000);
	My_class.insert(555, 12000);
	My_class.ptint();

	return 0;
}
