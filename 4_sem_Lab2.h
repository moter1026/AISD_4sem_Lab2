// 4_sem_Lab2.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <exception>


const char* BLACK_TEXT = "\033[30m";
const char* RED_TEXT = "\033[31m";
const char* GREEN_TEXT = "\033[32m";
const char* YELLOW_TEXT = "\033[33m";
const char* BLUE_TEXT = "\033[34m";
const char* LIGHT_BLUE_TEXT = "\033[36m";
const char* GRAY_TEXT = "\033[37m";
const char* RESET_TEXT = "\033[0m";


template<typename K, typename V>
class My_unordered_map {
	class Pair {
		K _key;
		V _value;

	public:
		K& getKey() { return this->_key; }
		V& getValue() { return this->_value; }
		K getKey() const noexcept { return this->_key; }
		V getValue() const noexcept { return this->_value; }

		void setKey(K key) { this->_key = key;}
		void setValue(V value) { this->_value = value; }

		Pair& operator=(const Pair& obj_1) {
			this->_key = obj_1.getKey();
			this->_value = obj_1.getValue();

			return *this;
		}

		Pair() : _key(-1), _value(0) {};
		Pair(K key, V value) : _value(value) {
			if (key < 0) throw std::runtime_error("Ключ не может быть меньше нуля");
			this->_key = key;
		};
		Pair(const Pair& obj) {
			this->_key = obj.getKey();
			this->_value = obj.getValue();
		}
		~Pair() = default;

		friend std::ostream& operator<<(std::ostream& stream, const Pair& pair) {
			stream << "(" << pair.getKey() << "," << pair.getValue() << ")";
			return stream;
		}
	};
	
	int A = 677;
	// Определяю размер машинного слова
	size_t MACHINE_WORD = sizeof(size_t);
	Pair* _arr_pair;
	size_t _size;

	// Возвращает индекс первого эл-та, имеющий ключ key
	size_t at(K key) const{
		checkKey(key);

		size_t index = this->hash(key);

		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == key) {
				return i;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() == key) {
				return i;
			}
		}
		return -1;
	}
	void checkKey(K key) const {
		if (key >= 0) return;
		throw std::runtime_error("Ключ не должен быть меньше нуля");
	}
public:
	size_t getSize() const noexcept { return this->_size; }
	Pair& getPair(size_t index) const noexcept { return this->_arr_pair[index]; }
	int hash(int key) const {
		double n;

		double A_machine_word_and_key = (double(this->A) / this->MACHINE_WORD * key);
		double modf = std::modf(A_machine_word_and_key, &n);
		return std::floor(this->_size * (modf));
	}
	/*int hash(std::string rome_number) const {
		
	}*/
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

	bool contains(K value) const {
		for (size_t i = 0; i < this->getSize(); ++i)
		{
			// Проверка на равенство значений и на то, чтобы ключ был валидным
			if (this->_arr_pair[i].getValue() == value && 
				this->_arr_pair[i].getKey() != -1) {
				return true;
			}
		}
		return false;
	}
	bool contains_key(int key) const {
		checkKey(key);

		if (this->at(key) != -1) return true;
		return false;
	}
	bool contains(int key, K value) const {
		checkKey(key);

		int index = this->hash(key);

		if (this->_arr_pair[index].getKey() == -1) {
			return false;
		}

		// Начинаем поиск с index, потому что более вероятно, что нужное
		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == key &&
				this->_arr_pair[i].getValue() == value) {
				return true;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() == key &&
				this->_arr_pair[i].getValue() == value) {
				return true;
			}
		}
		return false;
	}
	V* search(K key) const {
		checkKey(key);
		size_t index = this->at(key);
		if (index != -1) 
		{
			V& value = this->getPair(index).getValue();
			return &value;
		}
		return nullptr;
	}

	void insert(int key, K value) {
		checkKey(key);

		int index = this->hash(key);

		for (size_t i = index; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == -1) {
				this->_arr_pair[i] = Pair(key, value);
				return;
			}
		}
		for (size_t i = 0; i < index; ++i)
		{
			if (this->_arr_pair[i].getKey() == -1) {
				this->_arr_pair[i] = Pair(key, value);
				return;
			}
		}
		return;
	}
	// Вставляет эл-т, если до этого не было эл-тов с таким ключём.
	// Иначе заменяет у существующего эл-та значение value
	void insert_or_assign(K key, V value) {
		checkKey(key);

		size_t index = this->at(key);
		
		if (index == -1) {
			index = this->hash(key);

			for (size_t i = index; i < this->getSize(); ++i)
			{
				if (this->_arr_pair[i].getKey() == -1) {
					this->_arr_pair[i] = Pair(key, value);
					return;
				}
			}
			for (size_t i = 0; i < index; ++i)
			{
				if (this->_arr_pair[i].getKey() == -1) {
					this->_arr_pair[i] = Pair(key, value);
					return;
				}
			}
		}
		this->getPair(index).setValue(value);
	}
	bool erase(K key) {
		size_t index = this->at(key);

		if (index != -1)
		{
			this->getPair(index).setKey(-1);
			this->getPair(index).setValue(0);
			return true;
		}
		return false;
	}
	int count(K key) const {
		checkKey(key);

		int count = 0;
		for (size_t i = 0; i < this->getSize(); ++i)
		{
			if (this->_arr_pair[i].getKey() == key) {
				++count;
			}
		}
		return count;
	}
	
	My_unordered_map& operator=(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair[this->_size];

		for (size_t i = 0; i < this->_size; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}

		return *this;
	}

	My_unordered_map() {
		this->_size = 10;
		this->_arr_pair = new Pair[this->_size];
	};
	My_unordered_map(size_t size): _size(size) {
		this->_arr_pair = new Pair[size];
	}
	My_unordered_map(const My_unordered_map& obj) {
		this->_size = obj.getSize();
		this->_arr_pair = new Pair[this->_size];

		for (size_t i = 0; i < this->_size; ++i)
		{
			this->_arr_pair[i] = obj.getPair(i);
		}
	}

	~My_unordered_map() {
		delete[] this->_arr_pair;
	}
};