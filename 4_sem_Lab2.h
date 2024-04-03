// 4_sem_Lab2.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>


const char* BLACK_TEXT = "\033[30m";
const char* RED_TEXT = "\033[31m";
const char* GREEN_TEXT = "\033[32m";
const char* YELLOW_TEXT = "\033[33m";
const char* BLUE_TEXT = "\033[34m";
const char* LIGHT_BLUE_TEXT = "\033[36m";
const char* GRAY_TEXT = "\033[37m";
const char* RESET_TEXT = "\033[0m";


template<typename T>
class My_unordered_map {
	template<typename M>
	class Pair {
		int _key;
		M _value;

	public:
		int getKey() const { return this->_key; }
		M getValue() const { return this->_value; }

		Pair& operator=(const Pair& obj_1) {
			this->_key = obj_1.getKey();
			this->_value = obj_1.getValue();

			return *this;
		}

		Pair() = default;
		Pair(int key, M value) : _key(key), _value(value) {};
		Pair(const Pair& obj) {
			this->_key = obj.getKey();
			this->_value = obj.getValue();
		}

		friend std::ostream& operator<<(std::ostream& stream, const Pair<M>& pair) {
			stream << "(" << pair.getKey() << "," << pair.getValue() << ")";
			return stream;
		}
	};
	
	

	int A = 10000;
	// Определяю размер машинного слова
	size_t MACHINE_WORD = sizeof(size_t);

	Pair<T>* _arr_pair;
	size_t _size;

public:
	size_t getSize() const { return this->_size; }
	Pair<T> getPair(size_t index) const { return this->_arr_pair[index]; }
	int hash(int key) { return std::floor(this->_size * ((this->A / this->MACHINE_WORD * key) % 1)); }
	void ptint() const{
		std::cout << GREEN_TEXT << "Hash table with size = " << this->getSize() << " and method 'open andress'." << RESET_TEXT <<std::endl;
		
		// Заголовки колонок
		std::cout << std::setw(15) << std::left << "hash"
			<< std::setw(10) << std::left << "Pair" << std::endl;
		// Разделитель
		std::cout << std::setw(35) << std::setfill('-') << "" << std::endl;
		std::cout << std::setfill(' '); // Сбрасываем символ-заполнитель
		for (size_t i = 0; i < this->getSize(); i++)
		{
			// Данные
			std::cout << std::setw(15) << std::left << i
				<< std::setw(1) << std::left << this->getPair(i) << std::endl;
		}
	}

	My_unordered_map& operator=(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair<T>[this->_size];

		for (size_t i = 0; i < this->_size - 1; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}

		return *this;
	}

	My_unordered_map() = default;
	My_unordered_map(size_t size): _size(size) {
		this->_arr_pair = new Pair<T>[size];
	}
	My_unordered_map(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair<T>[this->_size];

		for (size_t i = 0; i < this->_size - 1; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}
	}

	~My_unordered_map() {
		this->A = 0;
		this->MACHINE_WORD = 0;
		this->_size = 0;

		delete[] this->_arr_pair;
	}
};