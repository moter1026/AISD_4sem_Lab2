// 4_sem_Lab2.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include <unordered_map>
#include <string>

#include "4_sem_Lab2.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");
	My_unordered_map<int, int> My_class(15);

	My_class.print();
	try {
		My_class.insert(124, 1000);
		My_class.insert(555, 2000);
		My_class.insert(333, 3000);
		My_class.insert(111, 4000);
		My_class.insert(111, 5000);
		My_class.insert(555, 6000);
		My_class.insert(111, 7000);

	
		My_class.print();

		/*My_class.insert(-111, 5000);
		My_class.print();*/

		std::cout << My_class.contains(2000) << "\n" <<
			My_class.contains_key(555) << "\n" <<
			My_class.contains(555, 2000) << std::endl;

		std::cout << GREEN_TEXT << "\n" << *My_class.search(333) << RESET_TEXT << std::endl;

		My_class.erase(555);
		std::cout << "После удаления эл-та" << std::endl;
		My_class.print();

		std::cout << YELLOW_TEXT << "Кол-во эл-тов с ключом 111 = " << My_class.count(111) << RESET_TEXT << std::endl;
		

		My_unordered_map<int, int> My_class2;
		My_class2 = My_class;

		std::cout << YELLOW_TEXT << "Приравниваем My_class2 к My_class через оператор ="  << RESET_TEXT << std::endl;
		std::cout << YELLOW_TEXT << "My_class2 :" << RESET_TEXT << std::endl;
		My_class2.print();

		My_class2.erase(555);
		std::cout << "После удаления эл-та в My_class2. My_class2:" << std::endl;
		My_class2.print();
		std::cout << "После удаления эл-та в My_class2. My_class:" << std::endl;
		My_class.print();

		std::cout << "\n\n";
		std::cout << YELLOW_TEXT << "Пытаюсь вставить эл-нт через метод insert_or_assign" << RESET_TEXT << std::endl;
		My_class2.insert_or_assign(444, 4444);
		My_class2.print();
		std::cout << "\n";
		std::cout << YELLOW_TEXT << "Теперь метод insert_or_assign должен заменить эл-нт с существующим ключём" << RESET_TEXT << std::endl;
		My_class2.insert_or_assign(444, 5555);
		My_class2.print();


		My_unordered_map<int, int> My_class3(My_class2);

		std::cout << YELLOW_TEXT << "Приравниваем My_class3 к My_class2 через конструктор копирования" << RESET_TEXT << std::endl;
		std::cout << YELLOW_TEXT << "My_class3 :" << RESET_TEXT << std::endl;
		My_class3.print();

		My_class3.erase(333);
		std::cout << "После удаления эл-та с ключём 333 в My_class3. My_class3:" << std::endl;
		My_class3.print();
		std::cout << "После удаления эл-та в My_class3. My_class2:" << std::endl;
		My_class2.print();

		std::cout << "\n\n";
		std::cout << YELLOW_TEXT << "Пытаюсь вставить эл-нт через метод insert_or_assign" << RESET_TEXT << std::endl;
		My_class3.insert_or_assign(777, 7007);
		My_class3.print();
		std::cout << "\n";
		std::cout << YELLOW_TEXT << "Теперь метод insert_or_assign должен заменить эл-нт с существующим ключём" << RESET_TEXT << std::endl;
		My_class3.insert_or_assign(777, 2024);
		My_class3.print();

		std::cout << "\n\n\n\n";
		std::cout << GREEN_TEXT << "Заполняем рандомными Римскими числами нашу хэш таблицу" << RESET_TEXT << std::endl;
		My_unordered_map<std::string, int>  Task2(20);
		Task2.random_insert();
		Task2.print();


		std::cout << "\n\n\n\n";
		std::cout << GREEN_TEXT << "Реализовал класс шаблонно, Можно передавать в виде строки римские числа" << RESET_TEXT << std::endl;
		My_unordered_map<std::string, int>  Task(10);

		Task.insert("XVIII", 18);
		Task.insert("DCXLIX", 649);
		Task.insert("XIX", 19);
		Task.insert("MMMCM", 3900);
		Task.insert("XXXIV", 34);
		Task.insert("XIX", 190);
		Task.print();

		std::cout << "\n\n\n\n";
		std::cout << LIGHT_BLUE_TEXT << "Задание по варианту (нужно перевести введённое пользователем римское число в арабский вид)" << RESET_TEXT << std::endl;
		std::string rome_number = " ";
		while (rome_number != "\n")
		{
			std::cout << YELLOW_TEXT << "Введите римское число заглавными латинскими буквами" << RESET_TEXT << std::endl;
			std::cin >> rome_number;
			if (rome_number == "exit") break;
			std::cout << GREEN_TEXT << "Число " << rome_number << " в арабском виде = " << Task.toArabian(rome_number) << RESET_TEXT << std::endl;
			std::cout << RED_TEXT << "\nДля выхода введите 'exit'" << RESET_TEXT << std::endl;
		}
		return 0;
	}
	catch (std::runtime_error err) {
		std::cout << std::string(RED_TEXT) << err.what() << std::string(RESET_TEXT);
	}
}
