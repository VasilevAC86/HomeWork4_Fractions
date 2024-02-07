#include"Fraction.h"
# include <iostream>
#include<string>

void show_properties(Fraction& obj); // для вывода свойств дроби

int main() {	
	// --------------------------- Исходные дроби -----------------------------
	Fraction f1(true, 5, 7);	
	simplification(f1);	// Упрощаем дробь	
	Fraction f2(true, 0.4);
	simplification(f2); // Упрощаем дробь	
	//Выводим в консоль дроби, используя перегрузку оператора << класса std
	std::cout << "\033[93mThe sourse fractions:\033[0m" << std::endl << "f1 = \033[92m";
	if (f1.GetSign())
		std::cout << f1.GetValue();
	else
		std::cout << '-' << f1.GetValue();
	std::cout << " = " << f1 << "\033[0m";	
	show_properties(f1); // Выводим в консоль св-ва дроби
	std::cout << "f2 = \033[92m";
	if (f2.GetSign())
		std::cout << f2.GetValue();
	else
		std::cout << " - " << f2.GetValue();
	std::cout << " = " << f2 << "\033[0m";	
	show_properties(f2);

	// --------------------------- Изменяем исходные дроби ----------------------------	
	std::cout << std::endl << "\033[93mDo you want to change these fractions?\033[0m" << std::endl \
		<< "Press \033[91m1\033[0m to change f1 \033[4mor\033[0m press \033[91m2\033[0m to change f2 \033[4mor\033[0m press \033[91mane other key\033[0m if everything suit you"\
		<< std::endl << "Your choice -> ";
	char my_Choice; // Переменная для хранения выбора пользователя
	std::cin >> my_Choice;
	if (my_Choice == '1' || my_Choice == '2') {
		while (my_Choice == '1' || my_Choice == '2') {
			std::cout << "\033[93mEnter the signed/unsigned real number\033[0m (for example, to create -1/2 enter -0.5, to create 1/2 enter 0.5) -> ";
			switch (my_Choice) {
			case '1':
				std::cin >> f1; // Вводим в объект Fraction вещественное число с консоли
				f1.SetSign(); // Уставнавливаем знак дроби
				f1.SetNumerator(); // Расчитываем величину числителя
				f1.SetDenominator(); // Расчитываем величину знаменателя
				simplification(f1); // Упрощаем дробь
				break;
			default:
				std::cin >> f2;
				f2.SetSign();
				f2.SetNumerator();
				f2.SetDenominator();
				simplification(f2);
			}
			std::cout << "Press \033[91m1\033[0m to change f1 \033[4mor\033[0m press \033[91m2\033[0m to change f2 \033[4mor\033[0m press \033[91mane other key\033[0m if everything suit you"\
				<< std::endl << "Your choice -> ";
			std::cin >> my_Choice;
		}
		std::cout << std::endl << "\033[96mYou entered the following fraction: \033[0m" << std::endl << "f1 = \033[92m" << f1 << "\033[0m";
		show_properties(f1);
		std::cout << "f2 = \033[92m" << f2 << "\033[0m";		
		show_properties(f2);
		std::cout << std::endl;
	}			
	
	// --------------------------- Реализация операторов математики ----------------------------
	std::cout << std::endl << "\033[93mMathematical operations on two fractions: \033[0m" << std::endl;
	Fraction result = f1 + f2;
	std::cout << "\033[93mf1 + f2 = \033[0m\t" << f1 << "\033[91m + \033[0m" << f2 << " = \033[92m\t" << result << "\033[0m";
	show_properties(result);	
	result = f1 - f2;
	std::cout << "\033[93mf1 - f2 = \033[0m\t" << f1 << "\033[91m - \033[0m" << f2 << " = \033[92m\t" << result << "\033[0m";
	show_properties(result);	
	result = f1 * f2;
	std::cout << "\033[93mf1 * f2 = \033[0m\t" << f1 << "\033[91m * \033[0m" << f2 << " = \033[92m\t" << result << "\033[0m";
	show_properties(result);	
	result = f1 / f2;
	std::cout << "\033[93mf1 / f2 = \033[0m\t" << f1 << "\033[91m / \033[0m" << f2 << " = \033[92m\t" << result << "\033[0m";
	show_properties(result);	
	result.~Fraction();
	std::cout << "\033[93mf1 += f2 = \033[0m\t" << f1 << "\033[91m += \033[0m" << f2 << " = \033[92m";
	f1 += f2;
	std::cout << f1 << "\033[0m \033[95m(Fraction f1 has been changed!)\033[0m";
	show_properties(f1);	
	std::cout << "\033[93mf1 -= f2 = \033[0m\t" << f1 << "\033[91m -= \033[0m" << f2 << " = \033[92m";
	f1 -= f2;
	std::cout << f1 << "\033[0m \033[95m(Fraction f1 has been changed!)\033[0m";
	show_properties(f1);	
	std::cout << "\033[93mf1++ = \033[0m\t" << f1 << "\033[91m++\033[0m = \033[92m";
	f1.operator++();
	simplification(f1);	
	std::cout << f1 << "\033[0m \033[95m(Fraction f1 has been changed!)\033[0m";
	show_properties(f1);	
	std::cout << "\033[93mf1-- = \033[0m\t" << f1 << "\033[91m--\033[0m = \033[92m";
	f1.operator--();
	simplification(f1);	
	std::cout << f1 << "\033[0m \033[95m(Fraction f1 has been changed!)\033[0m";
	show_properties(f1);
	
	return 0;
}

void show_properties(Fraction& obj) {
	if (obj.whole_number()) 
		std::cout << " (The fraction is a\033[96m whole number\033[0m and equal to " << "\033[92m" << obj.GetWholePart() << "\033[0m.";	
	else
		if (obj.proper())
			std::cout << " (The fraction is \033[96mproper!\033[0m";
		else {
			std::cout << " (The fraction isn't \033[96mproper\033[0m" << " and consists of a whole part \033[92m" << obj.GetWholePart() << \
				"\033[0m and non-integer part \033[92m" << obj.GetRemainder() << "\033[0m.";
		}
	std::cout << " Reciprocal fraction is \033[92m" << (obj.GetReciprocal()) << "\033[0m)" << std::endl;
}
