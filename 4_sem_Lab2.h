// 4_sem_Lab2.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <exception>
#include <random>

#define COUNT_ROME_SYMBOLS 7


const char* BLACK_TEXT = "\033[30m";
const char* RED_TEXT = "\033[31m";
const char* GREEN_TEXT = "\033[32m";
const char* YELLOW_TEXT = "\033[33m";
const char* BLUE_TEXT = "\033[34m";
const char* LIGHT_BLUE_TEXT = "\033[36m";
const char* GRAY_TEXT = "\033[37m";
const char* RESET_TEXT = "\033[0m";


template<typename K, typename V>
class Pair {
	K* _key;
	V* _value;

public:
	K* getKey() noexcept { return this->_key; }
	V* getValue() noexcept { return this->_value; }

	void setKey(K* key) { this->_key = key; }
	void setValue(V* value) { this->_value = value; }

	Pair& operator=(const Pair<K, V>& obj_1) {
		if (this != &obj_1) {
			if (obj_1._key != nullptr) {
				delete this->_key;
				delete this->_value;
				this->_key = new K(*obj_1._key);
				this->_value = new V(*obj_1._value);
			}
		}
		return *this;
	}

	Pair() : _key(nullptr), _value(nullptr) {};
	Pair(K* key, V* value) : _value(value) {
		this->_key = key;
	};
	Pair(K key, V value) {
		this->_key = new K(key);
		this->_value = new V(value);
	}
	Pair(Pair& obj) {
		this->_key = new K(*(obj.getKey()));
		this->_value = new V(*(obj.getValue()));
	}
	~Pair() {
		delete this->_key;
		delete this->_value;
	};

	friend std::ostream& operator<<(std::ostream& stream, Pair& pair) {
		if (pair.getKey() == nullptr) {
			stream << "(" << pair.getKey() << "," << pair.getValue() << ")";
		}
		else {
			stream << "(" << *(pair.getKey()) << "," << *(pair.getValue()) << ")";
		}
		return stream;
	}
};

template<typename K, typename V>
class My_unordered_map {
	int A = 677;
	// Определяю размер машинного слова
	size_t MACHINE_WORD = sizeof(size_t);
	Pair<K, V>* _arr_pair;
	size_t _size;

	Pair<char, int>* ROME_EQUAL = setRomeEqual();

	Pair<char, int>* setRomeEqual() {
		std::string symbols = "IVXLCDM";
		int values[7]{ 1, 5, 10, 50, 100, 500, 1000 };

		Pair<char, int>* rome_equal = new Pair<char, int>[COUNT_ROME_SYMBOLS];

		for (size_t i = 0; i < COUNT_ROME_SYMBOLS; ++i)
		{
			rome_equal[i] = Pair(new char(symbols[i]), new V(values[i]));
		}

		return rome_equal;
	}
	int getIndexInRomeNumber(const char symb) {
		for (size_t i = 0; i < COUNT_ROME_SYMBOLS; ++i)
		{
			if (symb == *(ROME_EQUAL[i].getKey())) {
				return i;
			}
		}
		return -1;
	}
	

	// Возвращает индекс первого эл-та, имеющий ключ key
	size_t at(K key) const{
		size_t index = this->hash(key);

		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() != nullptr &&
				*(this->_arr_pair[i].getKey()) == key) {
				return i;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() != nullptr &&
				*(this->_arr_pair[i].getKey()) == key) {
				return i;
			}
		}
		return -1;
	}
public:
	size_t getSize() const noexcept { return this->_size; }
	Pair<K, V>& getPair(size_t index) const noexcept { return this->_arr_pair[index]; }
	
	int toArabian(std::string rome_number) {
		int res_number = 0;
		for (size_t i = 0; rome_number[i] != '\0'; ++i)
		{
			char now_symb = rome_number[i];
			char next_symb = rome_number[i + 1];
			// 1,2,4 - индексы символов I,X,C, которые могут стоять перед большим числом, уменьшая его
			int now_ind = getIndexInRomeNumber(now_symb);
			int next_ind = getIndexInRomeNumber(next_symb);
			if (next_ind != -1 &&
				(now_ind == 0 ||
					now_ind == 2 ||
					now_ind == 4) &&
				(now_ind == next_ind - 1 ||
					now_ind == next_ind - 2))
			{
				res_number += *(ROME_EQUAL[next_ind].getValue()) -
					*(ROME_EQUAL[now_ind].getValue());
				now_symb = next_symb;
				++i;
			}
			else if (getIndexInRomeNumber(now_symb) != -1) {
				res_number += *(ROME_EQUAL[now_ind].getValue());
			}
		}
		return res_number;
	}
	std::string arabicToRome(int number) {
		const int arabicNums[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
		const std::string romanNums[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

		std::string result = "";

		for (int i = 0; i < 13; i++) {
			while (number >= arabicNums[i]) {
				result += romanNums[i];
				number -= arabicNums[i];
			}
		}

		return result;
	}

	int hash(K key) const {
		double n;

		double A_machine_word_and_key = (double(this->A) / this->MACHINE_WORD * key);
		double modf = std::modf(A_machine_word_and_key, &n);
		return std::floor(this->_size * (modf));
	}
	int hash(std::string rome_number) {
		size_t number = this->toArabian(rome_number);

		double n;

		double A_machine_word_and_key = (double(this->A) / this->MACHINE_WORD * number);
		double modf = std::modf(A_machine_word_and_key, &n);
		return std::floor(this->_size * (modf));
	}
	void print() const noexcept {
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
	bool contains(V value) const {
		for (size_t i = 0; i < this->getSize(); ++i)
		{
			// Проверка на равенство значений и на то, чтобы ключ был валидным
			if (this->_arr_pair[i].getKey() != nullptr &&
				*(this->_arr_pair[i].getValue()) == value) {
				return true;
			}
		}
		return false;
	}
	bool contains(K key, K value) const {
		int index = this->hash(key);

		if (this->_arr_pair[index].getKey() == nullptr) {
			return false;
		}

		// Начинаем поиск с index, потому что более вероятно, что нужное
		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() != nullptr &&
				*(this->_arr_pair[i].getKey()) == key &&
				*(this->_arr_pair[i].getValue()) == value) {
				return true;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() != nullptr &&
				*(this->_arr_pair[i].getKey()) == key &&
				*(this->_arr_pair[i].getValue()) == value) {
				return true;
			}
		}
		return false;
	}
	bool contains_key(K key) const {
		if (this->at(key) != -1) return true;
		return false;
	}
	V* search(K key) const {
		size_t index = this->at(key);
		if (index != -1) 
		{
			V* value = this->getPair(index).getValue();
			return value;
		}
		return nullptr;
	}
	void insert(K key, V value) {
		int index = this->hash(key);

		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == nullptr) {
				this->_arr_pair[i] = Pair(key, value);
				return;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() == nullptr) {
				this->_arr_pair[i] = Pair(key, value);
				return;
			}
		}
		return;
	}
	void random_insert() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 100);

		for (size_t i = 0; i < this->getSize(); ++i)
		{
			int rand = dis(gen);
			std::string rome_number = arabicToRome(rand);
			insert(rome_number, rand);
		}
	}
	// Вставляет эл-т, если до этого не было эл-тов с таким ключём.
	// Иначе заменяет у существующего эл-та значение value
	void insert_or_assign(K key, V value) {
		size_t index = this->at(key);
		
		if (index == -1) {
			index = this->hash(key);

			for (size_t i = index; i < this->getSize(); ++i)
			{
				if (this->_arr_pair[i].getKey() == nullptr) {
					this->_arr_pair[i] = Pair(new K(key), new V(value));
					return;
				}
			}
			for (size_t i = 0; i < index; ++i)
			{
				if (this->_arr_pair[i].getKey() == nullptr) {
					this->_arr_pair[i] = Pair(new K(key), new V(value));
					return;
				}
			}
		}
		this->getPair(index).setValue(new V(value));
	}
	bool erase(K key) {
		size_t index = this->at(key);

		if (index != -1)
		{
			this->getPair(index).setKey(nullptr);
			this->getPair(index).setValue(nullptr);
			return true;
		}
		return false;
	}
	int count(K key) const {
		int count = 0;
		for (size_t i = 0; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == nullptr) continue;
			Pair<K, V> pair = this->_arr_pair[i];
			if (*(pair.getKey()) == key) {
				++count;
			}
		}
		return count;
	}
	
	My_unordered_map& operator=(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair<K, V>[this->_size];

		for (size_t i = 0; i < this->_size; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}

		return *this;
	}


	My_unordered_map() {
		this->_size = 10;
		this->_arr_pair = new Pair<K, V>[this->_size];
	};
	My_unordered_map(size_t size): _size(size) {
		this->_arr_pair = new Pair<K, V>[size];
	}
	My_unordered_map(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair<K, V>[this->_size];

		for (size_t i = 0; i < this->_size; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}
	}

	~My_unordered_map() {
		delete[] this->_arr_pair;
	}
};