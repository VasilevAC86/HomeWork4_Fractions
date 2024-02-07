#include "Fraction.h"
#include<iostream>
#include<string>

Fraction::Fraction(bool sign, double value) {
	this->value_ = value;
	this->sign_ = sign;
	if (value < 0) {
		this->sign_ = false;
		this->value_ = value * (-1);
	}
	if (value == 0) {
		numerator_ = 0;
		denominator_ = 1;
		return;
	}
	int factor = std::to_string(value_).length() - std::to_string(value_).find('.'); // Кол-во знаков после точки
	numerator_ = value_ * pow(10, factor);
	denominator_ = pow(10, factor);	
}

Fraction Fraction::GetRemainder() const {
	Fraction result;
	result.denominator_ = denominator_;
	result.numerator_ = numerator_ - (numerator_ / denominator_) * denominator_;
	result.value_ = result.numerator_ / (double)result.denominator_;
	simplification(result);
	return result;
}

Fraction Fraction::GetReciprocal() const {
	Fraction reciprocal;	
	if (numerator_ == 0) {
		reciprocal.denominator_ = 1;
		reciprocal.numerator_ = 0;
	}
	else {
		reciprocal.denominator_ = numerator_;	
		reciprocal.numerator_ = denominator_;
	}	
	reciprocal.sign_ = sign_;
	reciprocal.value_ = reciprocal.numerator_ / (double)reciprocal.denominator_;
	simplification(reciprocal);
	return reciprocal;
}

void Fraction::SetNumerator() {
	if (value_ == 0) {
		numerator_ = 0;
		return;
	}		
	int factor = std::to_string(value_).length() - std::to_string(value_).find('.'); // Кол-во знаков после точки
	numerator_ = value_ * pow(10, factor);
}

void Fraction::SetDenominator() {	
	if (value_ == 0) {
		denominator_ = 1;
		return;
	}
	int factor = std::to_string(value_).length() - std::to_string(value_).find('.'); // Кол-во знаков после точки
	denominator_ = pow(10, factor);
}

void Fraction::SetSign() {	
	if (value_ < 0) {
		this->sign_ = false;
		this->value_ = value_ * (-1);
	}
	else {
		this->sign_ = true;
		this->value_ = value_;
	}
}

void Fraction::operator++() {
	if (sign_) {
		numerator_ += denominator_;		
		return;
	}
	if (numerator_ == denominator_) {
		numerator_ = 0;
		denominator_ = 1;
		sign_ = true;
		return;
	}
	if (numerator_ > denominator_) {
		numerator_ -= denominator_;
		return;
	}
	numerator_ = denominator_ - numerator_;
	sign_ = true;	
}

void Fraction::operator--() {
	if (sign_ == false) {
		numerator_ += denominator_;
		return;
	}
	if (numerator_ == denominator_) {
		numerator_ = 0;
		denominator_ = 1;		
		return;
	}
	if (numerator_ > denominator_) {
		numerator_ -= denominator_;
		return;
	}
	numerator_ = denominator_ - numerator_;
	sign_ = false;
}

std::ostream& operator<<(std::ostream& out, const Fraction& obj) {
	if (obj.sign_)
		return (out << obj.numerator_ << '/' << obj.denominator_ << "\033[0m");
	return (out << '-' << obj.numerator_ << '/' << obj.denominator_ << "\033[0m");
	// TODO: insert return statement here
}

Fraction operator+(const Fraction& obj1, const Fraction& obj2) {
	Fraction result; // новый объект класса (результата вычисления)	
	result.denominator_ = lcd(obj1.denominator_, obj2.denominator_); // находим наименьший общий делитель слагаемых дробей				
	if ((obj1.sign_ && obj2.sign_) || (obj1.sign_ == false && obj2.sign_ == false)) { // Блок вычислений, когда обе дроби однознаковые
		result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) + obj2.numerator_ * (result.denominator_ / obj2.denominator_);
		if (obj1.sign_ == false)
			result.sign_ = false;		
		return result;
	}	
	if (obj1.sign_) { // Блок вычислений, когда только первая дробь положительная
		if (obj2.numerator_ * (result.denominator_ / obj2.denominator_) <= obj1.numerator_ * (result.denominator_ / obj1.denominator_))
			result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) - obj2.numerator_ * (result.denominator_ / obj2.denominator_);
		else {
			result.numerator_ = obj2.numerator_ * (result.denominator_ / obj2.denominator_) - obj1.numerator_ * (result.denominator_ / obj1.denominator_);
			result.sign_ = false;
		}			
		return result;
	}
	// Блок вычислений, когда только вторая дробь положительная
	if (obj1.numerator_ * (result.denominator_ / obj1.denominator_) <= obj2.numerator_ * (result.denominator_ / obj2.denominator_))
		result.numerator_ = obj2.numerator_ * (result.denominator_ / obj2.denominator_) - obj1.numerator_ * (result.denominator_ / obj1.denominator_);
	else {
		result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) - obj2.numerator_ * (result.denominator_ / obj2.denominator_);
		result.sign_ = false;
	}		
	return result;
}

Fraction operator-(const Fraction& obj1, const Fraction& obj2) {
	Fraction result; // новый объект класса (результата вычисления)
	result.denominator_ = lcd(obj1.denominator_, obj2.denominator_);
	if (obj1.sign_ && obj2.sign_) { // Блок вычислений, когда обе дроби положительные
		if (obj1.numerator_ * (result.denominator_ / obj1.denominator_) >= obj2.numerator_ * (result.denominator_ / obj2.denominator_))
			result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) - obj2.numerator_ * (result.denominator_ / obj2.denominator_);
		else {
			result.numerator_ = obj2.numerator_ * (result.denominator_ / obj2.denominator_) - obj1.numerator_ * (result.denominator_ / obj1.denominator_);
			result.sign_ = false;
		}
		return result;
	}
	if (obj1.sign_ == false && obj2.sign_ == false) { // Блок вычислений, когда обе дроби отрицательные
		if (obj1.numerator_ * (result.denominator_ / obj1.denominator_) >= obj2.numerator_ * (result.denominator_ / obj2.denominator_)) {
			result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) - obj2.numerator_ * (result.denominator_ / obj2.denominator_);
			result.sign_ = false;
		}
		else
			result.numerator_ = obj2.numerator_ * (result.denominator_ / obj2.denominator_) - obj1.numerator_ * (result.denominator_ / obj1.denominator_);
		return result;
	}
	if (obj1.sign_ == false) { // Блок вычислений, когда только первая дробь отрицательная
		result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) + obj2.numerator_ * (result.denominator_ / obj2.denominator_);
		result.sign_ = false;
		return result;
	}
	// Блок вычислений, когда только вторая дробь отрицательная
	result.numerator_ = obj1.numerator_ * (result.denominator_ / obj1.denominator_) + obj2.numerator_ * (result.denominator_ / obj2.denominator_);
	return result;
}

Fraction operator*(const Fraction& obj1, const Fraction& obj2) {
	Fraction result;
	result.denominator_ = obj1.denominator_ * obj2.denominator_;
	result.numerator_ = obj1.numerator_ * obj2.numerator_;
	if ((obj1.sign_ && obj2.sign_ == false) || (obj1.sign_ == false && obj2.sign_)) // Если исходные дроби разнознаковые, то
		result.sign_ = false;
	if (obj1.numerator_ == 0 || obj2.numerator_ == 0)
		result.sign_ = true;
	simplification(result);
	return result;
}

Fraction operator/(const Fraction& obj1, const Fraction& obj2) {
	Fraction result;
	result.numerator_ = obj1.numerator_ * obj2.denominator_;
	result.denominator_ = obj1.denominator_ * obj2.numerator_;
	if ((obj1.sign_ && obj2.sign_ == false) || (obj1.sign_ == false && obj2.sign_)) // Если исходные дроби разнознаковые, то
		result.sign_ = false;
	simplification(result);
	return result;
}

unsigned long long Evklid(unsigned long long num1, unsigned long long num2) {
	while (num1 != num2)
		if (num1 > num2)
			num1 -= num2;
		else
			num2 -= num1;
	return num1;
}

unsigned long long lcd(unsigned long long num1, unsigned long long num2) {
	if (num1 == num2) // Если знаменатели дробей одинаковые, то
		return num1; 
	// иначе вычисляем наименьший общий знаменатель дробей
	unsigned long long factor = Evklid(num1, num2); // Реализуем алгоритм Евклида
	if (factor == 1) // Если знаменатели дробей могут разделиться только на 1, то
		return (num1 * num2); // общим знаменателем может быть только результат перемножения знаменателей дробей,	
	else // иначе, используя тернарные операторы, возвращаем наименьший из всех возможных общих знаменателей
		if (num1 % num2 == 0)
			return num1;
		else
			if (num2 % num1 == 0)
				return num2;
			else
				return ((num1 < num2 ? num1 : num2 / factor) * (num1 > num2 ? num1 : num2));			
}

void simplification(Fraction& obj) {
	int NOD = Evklid(obj.numerator_, obj.denominator_);
	if (NOD == 1)
		return;
	obj.numerator_ /= NOD;
	obj.denominator_ /= NOD;
}

bool Fraction::proper() {
	if (numerator_ < denominator_) 		
		return true;		
	return false;	
}

bool Fraction::whole_number() {
	if (numerator_ % denominator_ == 0) 		
		return true;	
	return false;
}
