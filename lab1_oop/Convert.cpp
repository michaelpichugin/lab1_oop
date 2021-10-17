#include "Convert.h"

Convert::Convert()
{
	work = true;
	num = ""; // Введенное число
	choice = 0; // Для выбора

	while (work)
	{
		input_num(num); // Введите число
		menu_1(choice); // В какой системе введено?

		switch (choice)
		{
		case 1: // 2
		{
			/*
			* -----------------------------------------------
			* Определяем положительность числа
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			/*
			* -----------------------------------------------
			* Проверка на корректность ввода
			* -----------------------------------------------
			*/
			int comma = 0;

			// Если ввод корректен
			if (check_correct_input_binary(negative, comma, num))
			{
				menu_1_1(choice); // В какую систему конвертнуть?)

				/*
				* -----------------------------------------------
				*  Конвертируем в десятичную степень
				* -----------------------------------------------
				*/
				int decimal = 0; // целый
				double decimal_fractional = 0.0; // дробный
				int fractional_num = 0; // чисел после запятой

				convert_2_to_10(negative, comma, num, decimal, decimal_fractional, fractional_num);

				switch (choice)
				{
				case 1: // В 10
				{
					/*
					* Результат конвертирования и проверка дроби
					*/

					if (comma == 0) // Если числитель целое
					{
						cout << "Десятичная: " << decimal << endl;
						system("pause");
						system("cls");
					}
					else if (comma > 0) // Если числитель дробное
					{
						cout << "Десятичная: ";
						cout.precision(fractional_num);
						cout << std::fixed << decimal_fractional << endl;
						system("pause");
						system("cls");
					}
					break;
				}
				case 2: // В 16
				{
					/*
					* -----------------------------------------------
					*  Конвертируем в шестнадцатеричную степень
					* -----------------------------------------------
					*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
					*/
					convert_2_to_16(negative, comma, decimal, decimal_fractional);
					break;
				}
				}
			}
			else cout << "Введенное число не корректно" << endl;

			break;
		}
		case 2: // 10
		{
			/*
			* -----------------------------------------------
			* Определяем положительность чисел
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			/*
			* -----------------------------------------------
			* Проверка на корректность ввода
			* -----------------------------------------------
			*/
			int comma = 0;
			int decimal = 0; // целый
			double decimal_fractional = 0.0; // дробный

			/// ВВОД КОРРЕКТЕН
			if (check_correct_input_decimal(negative, comma, num))
			{
				///
				/// В какую систему счисления перевести число?
				///
				menu_2(choice);

				switch (choice)
				{
				case 1: // В 2
				{
					/*
					* -----------------------------------------------
					* КОНВЕРТИРУЕМ В ДВОИЧНОЕ ЧИСЛО
					* -----------------------------------------------
					*/
					convert_10_to_2(negative, comma, num, decimal, decimal_fractional);
					break;
				}
				case 2: // В 16
				{
					/*
					* -----------------------------------------------
					*  Конвертируем в шестнадцатеричную степень
					* -----------------------------------------------
					*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
					*/
					convert_10_to_16(negative, comma, num, decimal);
					break;
				}
				}
			}
			else cout << "Введенное число не корректно" << endl;

			break;
		}
		case 3: // 16
		{
			/*
			* -----------------------------------------------
			* Определяем положительность чисел
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			// Проверяем число
			int comma = 0;

			// Если ввод корректен => Конвертируем
			if (check_correct_input_hex(negative, comma, num))
			{
				///
				/// В какую систему счисления перевести число?
				///
				menu_3(choice);

				/*
				* -----------------------------------------------
				*  Конвертируем в десятичную степень
				* -----------------------------------------------
				*/
				int decimal = 0; // целый
				double decimal_fractional = 0.0; // дробный
				int fractional_num = 0; // чисел после запятой

				convert_16_to_10(negative, comma, num, decimal, decimal_fractional, fractional_num);

				switch (choice)
				{
				case 1: // В 2
				{
					convert_16_to_2(negative, comma, num, decimal, decimal_fractional);
					break;
				}
				case 2: // В 10
				{
					/// РЕЗУЛЬТАТ КОНВЕРТИРОВАНИЯ
					if (comma == 0) // Если числитель целое
					{
						cout << "Десятичная: " << decimal << endl;
						system("pause");
						system("cls");
					}
					else if (comma > 0) // Если числитель дробное
					{
						string df = to_string(decimal_fractional);
						if (negative) df.erase(0, 2);
						else df.erase(0, 1);
						df = to_string(decimal) + df;
						cout << "Десятичная: " << df << endl;
						system("pause");
						system("cls");
					}
					break;
				}
				}
			}
			else cout << "Введенное число не корректно" << endl;

			break;
		}
		}
	}
}

void Convert::input_num(string& num)
{
	std::cout << "Введите число: ";
	std::cin >> num;
	system("cls");
}

void Convert::menu_1(unsigned int& choice)
{
	cout << "В какой системе счисления введено число?" << endl
		<< "1. Двоичная" << endl
		<< "2. Десятичная" << endl
		<< "3. Шестнадцатеричная" << endl
		<< "Выбор: ";
	cin >> choice;
	system("cls");
}

void Convert::menu_1_1(unsigned int& choice)
{
	cout << "В какую систему счисления перевести число?" << endl
		<< "1. Десятичную" << endl
		<< "2. Шестнадцатеричную" << endl
		<< "Выбор: ";
	cin >> choice;
	system("cls");
}

bool Convert::check_correct_input_binary(bool& negative, int& comma, string& num)
{
	bool correct_input = true;
	int i = 0;
	if (negative) i = 1; // Пропускаем минус
	for (; i < num.size(); i++)
	{
		if (num[i] != '0' && num[i] != '1' && num[i] != '.' && num[i] != ',')
			correct_input = false;
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // если запятых больше 1
		{
			correct_input = false;
			break;
		}
	}
	return correct_input;
}

void Convert::convert_2_to_10(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional, int& fractional_num)
{
	/*
	* -----------------------------------------------
	*  Конвертируем в десятичную степень
	* -----------------------------------------------
	*/

	if (comma == 0) // Если числитель целый
	{
		for (int i = num.size() - 1; i > -1; i--)
			if (num[i] == '1')
				decimal += pow(2, num.size() - (i + 1));
		if (negative) decimal *= -1.0;
	}
	else // Если число дробное
	{
		// посчитаем сколько чисел после запятой
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		// Удаляем разделитель
		auto pos = num.find('.');
		if (pos != std::string::npos) num.erase(pos, 1);
		pos = num.find(',');
		if (pos != std::string::npos) num.erase(pos, 1);

		// Конвертируем
		for (int i = num.size(); i > -1; i--)
			if (num[i] == '1') // не учитываем нули
			{
				double pow = 1;
				int deg = (int)(num.size() - (i + 1 + fractional_num));

				if (deg < 0) { // если степень отрицательная
					deg = -deg;
					for (long i = 0; i < deg; i++)
						pow *= 2;
					pow = 1 / pow;
				}
				else // если степень положительная
					for (long i = 0; i < deg; i++)
						pow *= 2;

				decimal_fractional += pow;
			}
		if (negative) decimal_fractional *= -1.0;
	}
}

void Convert::convert_2_to_16(bool& negative, int& comma, int& decimal, double& decimal_fractional)
{
	/*
	* -----------------------------------------------
	*  Конвертируем в шестнадцатеричную степень
	* -----------------------------------------------
	*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
	*/
	char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
	int		remainder,
		remainder_z,
		remainder_eq;
	string	hexadecimal = "",
		hexadecimalFraction_num_left = "",
		hexadecimalFraction_num_right = "",
		hex;

	if (comma == 0) // Если число целое
	{
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 16; // Остаток 
			decimal = decimal / 16; // Следующее число для деления
			hexadecimal += dictionary[remainder];
		} while (decimal != 0);

		// Реверс строки
		if (negative) hex = "-"; else hex = "";
		for (int i = hexadecimal.size(); i > -1; i--)
			hex += hexadecimal[i];

		// Результат перевода в шестнадцатеричную
		cout << "Шестнадцатеричная: " << hex << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // Если число дробное
	{
		// Конвертируем в текст сохраняя точность
		std::ostringstream out;
		out << std::setprecision(14) << decimal_fractional;
		string num_str = out.str();
		out.str("");

		long long num_left, num_right; // целая и дробная часть
		string num_left_str = "", num_right_str = "";

		// левая часть
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = 0; j < i; j++)
					num_left_str += num_str[j];
				break;
			}

		// правая часть
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = ++i; j < num_str.size(); j++)
					num_right_str += num_str[j];
				break;
			}

		// конвертируем в long long левую и правую часть
		std::istringstream(num_left_str) >> num_left;
		std::istringstream(num_right_str) >> num_right;

		// Конвертируем левую часть числителя
		if (negative) num_left *= -1; // Делаем положительным
		do
		{
			remainder = num_left % 16; // Остаток 
			num_left = num_left / 16; // Следующее число для деления
			hexadecimalFraction_num_left += dictionary[remainder];

		} while (num_left != 0);

		// Конвертируем правую часть числителя
		num_right_str = "0," + std::to_string(num_right);
		double num_right_double = std::stod(num_right_str);

		while (true)
		{
			num_right_double *= 16;
			num_right_str = std::to_string(num_right_double);

			string t = ""; // Числа после запятой
			for (int i = 0; i < num_right_str.size(); i++)
			{
				if (num_right_str[i] == ',' || num_right_str[i] == '.')
				{
					string h = "";
					for (int k = 0; k < i; k++)
						h += num_right_str[k];
					hexadecimalFraction_num_right += dictionary[stoi(h)];
					num_right_double -= stoi(h);
					for (int j = i + 1; j < num_right_str.size(); j++)
						t += num_right_str[j];
					break;
				}
			}
			// Цепочка закончена
			if (stoi(t) == 0) break;
		}



		/// РЕВЕРС СТРОКИ
		if (negative) hexadecimal = "-"; else hexadecimal = "";
		for (int i = hexadecimalFraction_num_left.size(); i > -1; i--)
			hexadecimal += hexadecimalFraction_num_left[i];

		/// РЕЗУЛЬТАТ КОНВЕРТИРОВАНИЯ
		hexadecimal += "." + hexadecimalFraction_num_right;
		cout << "Шестнадцатеричная: " << hexadecimal << endl;
		system("pause");
		system("cls");
	}
}

void Convert::menu_2(unsigned int& choice)
{
	cout << "В какую систему счисления перевести число?" << endl
		<< "1. Двоичную" << endl
		<< "2. Шестнадцатеричную" << endl
		<< "Выбор: ";
	cin >> choice;
	system("cls");
}

bool Convert::check_correct_input_decimal(bool& negative, int& comma, string& num)
{
	int i = 0;
	bool correct_input = true;
	if (negative) i = 1; // Пропускаем минус
	for (; i < num.size(); i++)
	{
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // если запятых больше 1
		{
			correct_input = false;
			break;
		}
	}

	if (comma == 0 && correct_input) // Целое
	{
		// Убираем минус перед числом
		if (negative)
		{
			string temp = "";
			for (int i = 1; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}

		// Проверяем число на корректность
		if (!(num.find_first_not_of("0123456789") == std::string::npos))
			correct_input = false;

		// Возвращаем минус
		if (negative)
		{
			string temp = "-";
			for (int i = 0; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}
	}
	else if (correct_input) // Дробное
	{
		// Убираем минус перед числом
		if (negative)
		{
			string temp = "";
			for (int i = 1; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}

		// Проверяем число на корректность
		for (int i = 0; i < num.size(); i++)
		{
			if (num[i] == ',' || num[i] == '.')
			{
				string right = "";
				// Чтобы не выйти за границы
				if ((static_cast<unsigned long long>(i) + 1) < num.size())
					for (int j = i + 1; j < num.size(); j++)
						right += num[j];
				// Проверяем число на корректность
				if (!(right.find_first_not_of("0123456789") == std::string::npos))
					correct_input = false;

				string left = "";
				for (int j = 0; j < i; j++)
					left += num[j];
				// Проверяем число на корректность
				if (!(left.find_first_not_of("0123456789") == std::string::npos))
					correct_input = false;
			}
		}

		// Добавляем минус перед числом
		if (negative)
		{
			string temp = "-";
			for (int i = 0; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}
	}
	return correct_input;
}

void Convert::convert_10_to_2(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional)
{
	/*
	* -----------------------------------------------
	* КОНВЕРТИРУЕМ В ДВОИЧНОЕ ЧИСЛО
	* -----------------------------------------------
	*/

	string binary = ""; // целый
	string binary_fractional = ""; // дробный
	int fractional_num = 0; // чисел после запятой
	int remainder = 0;

	if (comma == 0) // Если числитель целый
	{
		decimal = std::stoi(num);
		// КОНВЕРТИРУЕМ ЧИСЛИТЕЛЬ
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 2; // Остаток 
			decimal = decimal / 2; // Следующее число для деления
			binary += to_string(remainder);
		} while (decimal != 0);

		// Реверс строки
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}
	else // Если числитель дробный
	{
		/// ЛЕВАЯ ЧАСТЬ

		decimal = std::stoi(num);
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 2; // Остаток 
			decimal = decimal / 2; // Следующее число для деления
			binary += to_string(remainder);
		} while (decimal != 0);

		/// ПРАВАЯ ЧАСТЬ

		decimal_fractional = std::stod(num);
		// посчитаем сколько чисел после запятой
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		string num_right_str = num;
		// Удаляем разделитель
		auto pos = num_right_str.find('.');
		if (pos != std::string::npos)
		{
			num_right_str.erase(pos, 1);
			num_right_str.erase(0, pos);
			num_right_str = "0," + num_right_str;
		}

		pos = num_right_str.find(',');
		if (pos != std::string::npos)
		{
			num_right_str.erase(pos, 1);
			num_right_str.erase(0, pos);
			num_right_str = "0," + num_right_str;
		}

		double num_right_double = std::stod(num_right_str);
		while (true)
		{
			num_right_double *= 2;
			num_right_str = std::to_string(num_right_double);

			string t = ""; // Числа после запятой
			for (int i = 0; i < num_right_str.size(); i++)
			{
				if (num_right_str[i] == ',' || num_right_str[i] == '.')
				{
					string h = "";
					for (int k = 0; k < i; k++)
						h += num_right_str[k];
					binary_fractional += h;
					num_right_double -= stoi(h);
					for (int j = i + 1; j < num_right_str.size(); j++)
						t += num_right_str[j];
					break;
				}
			}
			// Цепочка закончена
			if (stoi(t) == 0) break;
		}

		/// РЕВЕРС ЛЕВОЙ ЧАСТИ			
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}

	/// РЕЗУЛЬТАТ КОНВЕРТИРОВАНИЯ
	if (comma == 0) // Если числитель целое
	{
		cout << "Двоичная: " << binary << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // Если числитель дробное
	{
		binary += "." + binary_fractional;
		cout << "Двоичная: " << binary << endl;
		system("pause");
		system("cls");
	}
}

void Convert::convert_10_to_16(bool& negative, int& comma, string& num, int& decimal)
{
	/*
	* -----------------------------------------------
	*  Конвертируем в шестнадцатеричную степень
	* -----------------------------------------------
	*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
	*/
	char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
	int		remainder;
	string	hexadecimal = "",
		hexadecimalFraction_num_left = "",
		hexadecimalFraction_num_right = "",
		hex;

	if (comma == 0) // Если число целое
	{
		decimal = stoi(num);
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 16; // Остаток 
			decimal = decimal / 16; // Следующее число для деления
			hexadecimal += dictionary[remainder];
		} while (decimal != 0);

		// Реверс строки
		if (negative) hex = "-"; else hex = "";
		for (int i = hexadecimal.size(); i > -1; i--)
			hex += hexadecimal[i];

		// Результат перевода в шестнадцатеричную
		cout << "Шестнадцатеричная: " << hex << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // Если число дробное
	{
		string num_str = num;

		long long num_left, num_right; // целая и дробная часть
		string num_left_str = "", num_right_str = "";

		// левая часть
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = 0; j < i; j++)
					num_left_str += num_str[j];
				break;
			}

		// правая часть
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = ++i; j < num_str.size(); j++)
					num_right_str += num_str[j];
				break;
			}

		// конвертируем в long long левую и правую часть
		std::istringstream(num_left_str) >> num_left;
		std::istringstream(num_right_str) >> num_right;

		// Конвертируем левую часть числителя
		if (negative) num_left *= -1; // Делаем положительным
		do
		{
			remainder = num_left % 16; // Остаток 
			num_left = num_left / 16; // Следующее число для деления
			hexadecimalFraction_num_left += dictionary[remainder];

		} while (num_left != 0);

		// Конвертируем правую часть числителя
		num_right_str = "0," + std::to_string(num_right);
		double num_right_double = std::stod(num_right_str);

		while (true)
		{
			num_right_double *= 16;
			num_right_str = std::to_string(num_right_double);

			string t = ""; // Числа после запятой
			for (int i = 0; i < num_right_str.size(); i++)
			{
				if (num_right_str[i] == ',' || num_right_str[i] == '.')
				{
					string h = "";
					for (int k = 0; k < i; k++)
						h += num_right_str[k];
					hexadecimalFraction_num_right += dictionary[stoi(h)];
					num_right_double -= stoi(h);
					for (int j = i + 1; j < num_right_str.size(); j++)
						t += num_right_str[j];
					break;
				}
			}
			// Цепочка закончена
			if (stoi(t) == 0) break;
		}

		/// РЕВЕРС СТРОКИ
		if (negative) hexadecimal = "-"; else hexadecimal = "";
		for (int i = hexadecimalFraction_num_left.size(); i > -1; i--)
			hexadecimal += hexadecimalFraction_num_left[i];

		/// РЕЗУЛЬТАТ КОНВЕРТИРОВАНИЯ
		hexadecimal += "." + hexadecimalFraction_num_right;
		cout << "Шестнадцатеричная: " << hexadecimal << endl;
		system("pause");
		system("cls");
	}
}

bool Convert::check_correct_input_hex(bool& negative, int& comma, string& num)
{
	// Проверяем число
	bool correct_input = false;
	int i = 0;
	if (negative) i = 1; // Пропускаем минус
	char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
	int counter = 0;
	for (; i < num.size(); i++)
	{
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // если запятых больше 1
		{
			correct_input = false;
			break;
		}

		for (int j = 0; j < 16; j++)
			if (num[i] == dictionary[j])
				counter++;
	}
	if (comma == 1 && negative)
		if (counter != num.size() - 2) correct_input = false;
		else correct_input = true;

	if (comma == 0 && !negative)
		if (counter != num.size()) correct_input = false;
		else correct_input = true;

	if (comma == 1 && !negative)
		if (counter != num.size() - 1) correct_input = false;
		else correct_input = true;

	if (comma == 0 && negative)
		if (counter != num.size() - 1) correct_input = false;
		else correct_input = true;

	return correct_input;
}

void Convert::menu_3(unsigned int& choice)
{
	cout << "В какую систему счисления перевести число?" << endl
		<< "1. Двоичную" << endl
		<< "2. Десятичную" << endl
		<< "Выбор: ";
	cin >> choice;
	system("cls");
}

void Convert::convert_16_to_10(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional, int& fractional_num)
{
	/*
	* -----------------------------------------------
	*  Конвертируем в десятичную степень
	* -----------------------------------------------
	*/

	if (comma == 0) // Если числитель целый
	{
		char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
		for (int i = num.size() - 1; i > -1; i--)
		{
			int temp = 0;
			for (int k = 0; k < 16; k++)
				if (num[i] == dictionary[k])
					temp = k;

			decimal += temp * pow(16, num.size() - (i + 1));
		}
		if (negative) decimal *= -1.0;
	}
	else // Если число дробное
	{
		// посчитаем сколько чисел после запятой
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		// Левая часть
		char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
		decimal = 0;
		for (int i = num.size() - (fractional_num + 2); i > -1; i--)
		{
			int temp = 0;
			for (int k = 0; k < 16; k++)
				if (num[i] == dictionary[k])
					temp = k;
			int test = num.size() - (i + fractional_num + 2);
			decimal += temp * pow(16, num.size() - (i + fractional_num + 2));
		}
		if (negative) decimal *= -1.0;

		// Правая часть

		// Удаляем разделитель
		//auto pos = num.find('.');
		//if (pos != std::string::npos) num.erase(pos, 1);
		//pos = num.find(',');
		//if (pos != std::string::npos) num.erase(pos, 1);

		// Конвертируем
		for (int i = num.size(); i > -1; i--)
		{
			double pow = 1;
			int deg = (int)(num.size() - (i + 1 + fractional_num));

			if (deg < 0) { // если степень отрицательная
				deg = -deg;
				for (long i = 0; i < deg; i++)
					pow *= 16;

				int temp = 0;
				for (int k = 0; k < 16; k++)
					if (num[i] == dictionary[k])
						temp = k;

				pow = temp / pow;
			}
			else continue;

			decimal_fractional += pow;
		}
		if (negative) decimal_fractional *= -1.0;
	}
}

void Convert::convert_16_to_2(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional)
{
	/*
	* -----------------------------------------------
	* КОНВЕРТИРУЕМ В ДВОИЧНОЕ ЧИСЛО
	* -----------------------------------------------
	*/

	string binary = ""; // целый
	string binary_fractional = ""; // дробный
	int fractional_num = 0; // чисел после запятой
	int remainder = 0;

	if (comma == 0) // Если числитель целый
	{
		// КОНВЕРТИРУЕМ ЧИСЛИТЕЛЬ
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 2; // Остаток 
			decimal = decimal / 2; // Следующее число для деления
			binary += to_string(remainder);
		} while (decimal != 0);

		// Реверс строки
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}
	else // Если числитель дробный
	{
		/// ЛЕВАЯ ЧАСТЬ
		if (negative) decimal *= -1; // Делаем положительным
		do
		{
			remainder = decimal % 2; // Остаток 
			decimal = decimal / 2; // Следующее число для деления
			binary += to_string(remainder);
		} while (decimal != 0);

		/// ПРАВАЯ ЧАСТЬ
		string num_right_str = "";
		if (negative) decimal_fractional *= -1.0;
		while (true)
		{
			decimal_fractional *= 2;
			num_right_str = std::to_string(decimal_fractional);

			string t = ""; // Числа после запятой
			for (int i = 0; i < num_right_str.size(); i++)
			{
				if (num_right_str[i] == ',' || num_right_str[i] == '.')
				{
					string h = "";
					for (int k = 0; k < i; k++)
						h += num_right_str[k];
					binary_fractional += h;
					decimal_fractional -= stoi(h);
					for (int j = i + 1; j < num_right_str.size(); j++)
						t += num_right_str[j];
					break;
				}
			}
			// Цепочка закончена
			if (stoi(t) == 0) break;
		}

		/// РЕВЕРС ЛЕВОЙ ЧАСТИ			
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}

	/// РЕЗУЛЬТАТ КОНВЕРТИРОВАНИЯ
	if (comma == 0) // Если числитель целое
	{
		cout << "Двоичная: " << binary << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // Если числитель дробное
	{
		binary += "." + binary_fractional;
		cout << "Двоичная: " << binary << endl;
		system("pause");
		system("cls");
	}
}