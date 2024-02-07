#pragma once
#include<string>
#include<iostream>

class Fraction {
public:		
	// Параметрический конструктор для дроби
	Fraction(bool sign, int numerator, int denominator): sign_(sign), numerator_(numerator), denominator_(denominator), value_(numerator_/double(denominator_)) {}
	// Параметрический конструктор для числа с плавающей точкой
	explicit Fraction(bool sign, double value);
	Fraction() :sign_(true), numerator_(0), denominator_(1), value_(0) {} // Конструктор по умолчанию
	~Fraction() {}
	// Блок гэттэров
	double GetValue()const { return value_; }
	bool GetSign()const { return sign_; }
	unsigned long long GetNuratior()const { return this->numerator_; }
	unsigned long long GetDenomirator()const { return this->denominator_; }
	int GetWholePart()const { return (numerator_ / denominator_); } // Целая часть неправльной дроби
	Fraction GetRemainder()const; // остаток неправльной дроби после отброса целой части
	Fraction GetReciprocal()const; // возврат обратной дроби
	// Блок сэттэров	
	void SetNumerator();
	void SetDenominator();
	void SetSign();
	void SetValue(float value) { this->value_ = value; }
	// Прототипы методов-предикатов
	bool proper(); // Проверка правильности дроби
	bool whole_number(); // Проверка дроби на соответствие целому числу
	// Перегрузки операторов как методы класса
	void operator ++();
	void operator --();
	// Перегрузка оператора << класса std как дружественной фукнции для вывода объекта класса Fraction в консоль
	friend std::ostream& operator <<(std::ostream& out, const Fraction &obj);
	// Перегрузка оператора >> класса std как дружественной фукнции для ввода объекта класса Fraction в консоль
	friend std::istream& operator >>(std::istream& in, Fraction& obj) {	return (in >> obj.value_); }
	// Перегрузки операторов как дружественные функции
	friend Fraction operator +(const Fraction& obj1, const Fraction& obj2);
	friend Fraction operator -(const Fraction& obj1, const Fraction& obj2);
	friend Fraction operator *(const Fraction& obj1, const Fraction& obj2);
	friend Fraction operator /(const Fraction& obj1, const Fraction& obj2);
	friend void operator +=(Fraction& obj1, const Fraction& obj2) { obj1 = obj1 + obj2; simplification(obj1); }
	friend void operator -=(Fraction& obj1, const Fraction& obj2) { obj1 = obj1 - obj2; simplification(obj1); }	
	// Блок прототипов дружественных функций 
	friend void simplification(Fraction &obj); // для упрощения дроби	
private:
	// Блок полей для реализации математической дроби или числа с плавающей точкой
	bool sign_; // переменная для хранения знака (true - это "+", false "-")
	unsigned long long numerator_; // переменная для хранения значения числителя		
	unsigned long long denominator_; // переменная для хранения значения знаменателя*/	
	double value_; // переменная для хранения значения вещественного числа		
};

// Блок внещних функций
unsigned long long Evklid(unsigned long long num1, unsigned long long num2); // поиск общего знаменателя двух целых чисел (алгоритм Евклида)
unsigned long long lcd(unsigned long long num1, unsigned long long num2); // Прототип функции для поиска наименьшего общего знаменателя дробей