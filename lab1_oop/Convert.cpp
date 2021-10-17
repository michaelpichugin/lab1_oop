#include "Convert.h"

Convert::Convert()
{
	work = true;
	num = ""; // ��������� �����
	choice = 0; // ��� ������

	while (work)
	{
		input_num(num); // ������� �����
		menu_1(choice); // � ����� ������� �������?

		switch (choice)
		{
		case 1: // 2
		{
			/*
			* -----------------------------------------------
			* ���������� ��������������� �����
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			/*
			* -----------------------------------------------
			* �������� �� ������������ �����
			* -----------------------------------------------
			*/
			int comma = 0;

			// ���� ���� ���������
			if (check_correct_input_binary(negative, comma, num))
			{
				menu_1_1(choice); // � ����� ������� �����������?)

				/*
				* -----------------------------------------------
				*  ������������ � ���������� �������
				* -----------------------------------------------
				*/
				int decimal = 0; // �����
				double decimal_fractional = 0.0; // �������
				int fractional_num = 0; // ����� ����� �������

				convert_2_to_10(negative, comma, num, decimal, decimal_fractional, fractional_num);

				switch (choice)
				{
				case 1: // � 10
				{
					/*
					* ��������� ��������������� � �������� �����
					*/

					if (comma == 0) // ���� ��������� �����
					{
						cout << "����������: " << decimal << endl;
						system("pause");
						system("cls");
					}
					else if (comma > 0) // ���� ��������� �������
					{
						cout << "����������: ";
						cout.precision(fractional_num);
						cout << std::fixed << decimal_fractional << endl;
						system("pause");
						system("cls");
					}
					break;
				}
				case 2: // � 16
				{
					/*
					* -----------------------------------------------
					*  ������������ � ����������������� �������
					* -----------------------------------------------
					*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
					*/
					convert_2_to_16(negative, comma, decimal, decimal_fractional);
					break;
				}
				}
			}
			else cout << "��������� ����� �� ���������" << endl;

			break;
		}
		case 2: // 10
		{
			/*
			* -----------------------------------------------
			* ���������� ��������������� �����
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			/*
			* -----------------------------------------------
			* �������� �� ������������ �����
			* -----------------------------------------------
			*/
			int comma = 0;
			int decimal = 0; // �����
			double decimal_fractional = 0.0; // �������

			/// ���� ���������
			if (check_correct_input_decimal(negative, comma, num))
			{
				///
				/// � ����� ������� ��������� ��������� �����?
				///
				menu_2(choice);

				switch (choice)
				{
				case 1: // � 2
				{
					/*
					* -----------------------------------------------
					* ������������ � �������� �����
					* -----------------------------------------------
					*/
					convert_10_to_2(negative, comma, num, decimal, decimal_fractional);
					break;
				}
				case 2: // � 16
				{
					/*
					* -----------------------------------------------
					*  ������������ � ����������������� �������
					* -----------------------------------------------
					*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
					*/
					convert_10_to_16(negative, comma, num, decimal);
					break;
				}
				}
			}
			else cout << "��������� ����� �� ���������" << endl;

			break;
		}
		case 3: // 16
		{
			/*
			* -----------------------------------------------
			* ���������� ��������������� �����
			* -----------------------------------------------
			*/
			bool negative = false;
			if (num[0] == '-') negative = true;

			// ��������� �����
			int comma = 0;

			// ���� ���� ��������� => ������������
			if (check_correct_input_hex(negative, comma, num))
			{
				///
				/// � ����� ������� ��������� ��������� �����?
				///
				menu_3(choice);

				/*
				* -----------------------------------------------
				*  ������������ � ���������� �������
				* -----------------------------------------------
				*/
				int decimal = 0; // �����
				double decimal_fractional = 0.0; // �������
				int fractional_num = 0; // ����� ����� �������

				convert_16_to_10(negative, comma, num, decimal, decimal_fractional, fractional_num);

				switch (choice)
				{
				case 1: // � 2
				{
					convert_16_to_2(negative, comma, num, decimal, decimal_fractional);
					break;
				}
				case 2: // � 10
				{
					/// ��������� ���������������
					if (comma == 0) // ���� ��������� �����
					{
						cout << "����������: " << decimal << endl;
						system("pause");
						system("cls");
					}
					else if (comma > 0) // ���� ��������� �������
					{
						string df = to_string(decimal_fractional);
						if (negative) df.erase(0, 2);
						else df.erase(0, 1);
						df = to_string(decimal) + df;
						cout << "����������: " << df << endl;
						system("pause");
						system("cls");
					}
					break;
				}
				}
			}
			else cout << "��������� ����� �� ���������" << endl;

			break;
		}
		}
	}
}

void Convert::input_num(string& num)
{
	std::cout << "������� �����: ";
	std::cin >> num;
	system("cls");
}

void Convert::menu_1(unsigned int& choice)
{
	cout << "� ����� ������� ��������� ������� �����?" << endl
		<< "1. ��������" << endl
		<< "2. ����������" << endl
		<< "3. �����������������" << endl
		<< "�����: ";
	cin >> choice;
	system("cls");
}

void Convert::menu_1_1(unsigned int& choice)
{
	cout << "� ����� ������� ��������� ��������� �����?" << endl
		<< "1. ����������" << endl
		<< "2. �����������������" << endl
		<< "�����: ";
	cin >> choice;
	system("cls");
}

bool Convert::check_correct_input_binary(bool& negative, int& comma, string& num)
{
	bool correct_input = true;
	int i = 0;
	if (negative) i = 1; // ���������� �����
	for (; i < num.size(); i++)
	{
		if (num[i] != '0' && num[i] != '1' && num[i] != '.' && num[i] != ',')
			correct_input = false;
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // ���� ������� ������ 1
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
	*  ������������ � ���������� �������
	* -----------------------------------------------
	*/

	if (comma == 0) // ���� ��������� �����
	{
		for (int i = num.size() - 1; i > -1; i--)
			if (num[i] == '1')
				decimal += pow(2, num.size() - (i + 1));
		if (negative) decimal *= -1.0;
	}
	else // ���� ����� �������
	{
		// ��������� ������� ����� ����� �������
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		// ������� �����������
		auto pos = num.find('.');
		if (pos != std::string::npos) num.erase(pos, 1);
		pos = num.find(',');
		if (pos != std::string::npos) num.erase(pos, 1);

		// ������������
		for (int i = num.size(); i > -1; i--)
			if (num[i] == '1') // �� ��������� ����
			{
				double pow = 1;
				int deg = (int)(num.size() - (i + 1 + fractional_num));

				if (deg < 0) { // ���� ������� �������������
					deg = -deg;
					for (long i = 0; i < deg; i++)
						pow *= 2;
					pow = 1 / pow;
				}
				else // ���� ������� �������������
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
	*  ������������ � ����������������� �������
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

	if (comma == 0) // ���� ����� �����
	{
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 16; // ������� 
			decimal = decimal / 16; // ��������� ����� ��� �������
			hexadecimal += dictionary[remainder];
		} while (decimal != 0);

		// ������ ������
		if (negative) hex = "-"; else hex = "";
		for (int i = hexadecimal.size(); i > -1; i--)
			hex += hexadecimal[i];

		// ��������� �������� � �����������������
		cout << "�����������������: " << hex << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // ���� ����� �������
	{
		// ������������ � ����� �������� ��������
		std::ostringstream out;
		out << std::setprecision(14) << decimal_fractional;
		string num_str = out.str();
		out.str("");

		long long num_left, num_right; // ����� � ������� �����
		string num_left_str = "", num_right_str = "";

		// ����� �����
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = 0; j < i; j++)
					num_left_str += num_str[j];
				break;
			}

		// ������ �����
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = ++i; j < num_str.size(); j++)
					num_right_str += num_str[j];
				break;
			}

		// ������������ � long long ����� � ������ �����
		std::istringstream(num_left_str) >> num_left;
		std::istringstream(num_right_str) >> num_right;

		// ������������ ����� ����� ���������
		if (negative) num_left *= -1; // ������ �������������
		do
		{
			remainder = num_left % 16; // ������� 
			num_left = num_left / 16; // ��������� ����� ��� �������
			hexadecimalFraction_num_left += dictionary[remainder];

		} while (num_left != 0);

		// ������������ ������ ����� ���������
		num_right_str = "0," + std::to_string(num_right);
		double num_right_double = std::stod(num_right_str);

		while (true)
		{
			num_right_double *= 16;
			num_right_str = std::to_string(num_right_double);

			string t = ""; // ����� ����� �������
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
			// ������� ���������
			if (stoi(t) == 0) break;
		}



		/// ������ ������
		if (negative) hexadecimal = "-"; else hexadecimal = "";
		for (int i = hexadecimalFraction_num_left.size(); i > -1; i--)
			hexadecimal += hexadecimalFraction_num_left[i];

		/// ��������� ���������������
		hexadecimal += "." + hexadecimalFraction_num_right;
		cout << "�����������������: " << hexadecimal << endl;
		system("pause");
		system("cls");
	}
}

void Convert::menu_2(unsigned int& choice)
{
	cout << "� ����� ������� ��������� ��������� �����?" << endl
		<< "1. ��������" << endl
		<< "2. �����������������" << endl
		<< "�����: ";
	cin >> choice;
	system("cls");
}

bool Convert::check_correct_input_decimal(bool& negative, int& comma, string& num)
{
	int i = 0;
	bool correct_input = true;
	if (negative) i = 1; // ���������� �����
	for (; i < num.size(); i++)
	{
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // ���� ������� ������ 1
		{
			correct_input = false;
			break;
		}
	}

	if (comma == 0 && correct_input) // �����
	{
		// ������� ����� ����� ������
		if (negative)
		{
			string temp = "";
			for (int i = 1; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}

		// ��������� ����� �� ������������
		if (!(num.find_first_not_of("0123456789") == std::string::npos))
			correct_input = false;

		// ���������� �����
		if (negative)
		{
			string temp = "-";
			for (int i = 0; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}
	}
	else if (correct_input) // �������
	{
		// ������� ����� ����� ������
		if (negative)
		{
			string temp = "";
			for (int i = 1; i < num.size(); i++)
				temp += num[i];
			num = temp;
		}

		// ��������� ����� �� ������������
		for (int i = 0; i < num.size(); i++)
		{
			if (num[i] == ',' || num[i] == '.')
			{
				string right = "";
				// ����� �� ����� �� �������
				if ((static_cast<unsigned long long>(i) + 1) < num.size())
					for (int j = i + 1; j < num.size(); j++)
						right += num[j];
				// ��������� ����� �� ������������
				if (!(right.find_first_not_of("0123456789") == std::string::npos))
					correct_input = false;

				string left = "";
				for (int j = 0; j < i; j++)
					left += num[j];
				// ��������� ����� �� ������������
				if (!(left.find_first_not_of("0123456789") == std::string::npos))
					correct_input = false;
			}
		}

		// ��������� ����� ����� ������
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
	* ������������ � �������� �����
	* -----------------------------------------------
	*/

	string binary = ""; // �����
	string binary_fractional = ""; // �������
	int fractional_num = 0; // ����� ����� �������
	int remainder = 0;

	if (comma == 0) // ���� ��������� �����
	{
		decimal = std::stoi(num);
		// ������������ ���������
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 2; // ������� 
			decimal = decimal / 2; // ��������� ����� ��� �������
			binary += to_string(remainder);
		} while (decimal != 0);

		// ������ ������
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}
	else // ���� ��������� �������
	{
		/// ����� �����

		decimal = std::stoi(num);
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 2; // ������� 
			decimal = decimal / 2; // ��������� ����� ��� �������
			binary += to_string(remainder);
		} while (decimal != 0);

		/// ������ �����

		decimal_fractional = std::stod(num);
		// ��������� ������� ����� ����� �������
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		string num_right_str = num;
		// ������� �����������
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

			string t = ""; // ����� ����� �������
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
			// ������� ���������
			if (stoi(t) == 0) break;
		}

		/// ������ ����� �����			
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}

	/// ��������� ���������������
	if (comma == 0) // ���� ��������� �����
	{
		cout << "��������: " << binary << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // ���� ��������� �������
	{
		binary += "." + binary_fractional;
		cout << "��������: " << binary << endl;
		system("pause");
		system("cls");
	}
}

void Convert::convert_10_to_16(bool& negative, int& comma, string& num, int& decimal)
{
	/*
	* -----------------------------------------------
	*  ������������ � ����������������� �������
	* -----------------------------------------------
	*  A = 10, B = 11, C = 12, D = 13, E = 14, F = 15
	*/
	char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
	int		remainder;
	string	hexadecimal = "",
		hexadecimalFraction_num_left = "",
		hexadecimalFraction_num_right = "",
		hex;

	if (comma == 0) // ���� ����� �����
	{
		decimal = stoi(num);
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 16; // ������� 
			decimal = decimal / 16; // ��������� ����� ��� �������
			hexadecimal += dictionary[remainder];
		} while (decimal != 0);

		// ������ ������
		if (negative) hex = "-"; else hex = "";
		for (int i = hexadecimal.size(); i > -1; i--)
			hex += hexadecimal[i];

		// ��������� �������� � �����������������
		cout << "�����������������: " << hex << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // ���� ����� �������
	{
		string num_str = num;

		long long num_left, num_right; // ����� � ������� �����
		string num_left_str = "", num_right_str = "";

		// ����� �����
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = 0; j < i; j++)
					num_left_str += num_str[j];
				break;
			}

		// ������ �����
		for (int i = 0; i < num_str.size(); i++)
			if (num_str[i] == '.' || num_str[i] == ',')
			{
				for (int j = ++i; j < num_str.size(); j++)
					num_right_str += num_str[j];
				break;
			}

		// ������������ � long long ����� � ������ �����
		std::istringstream(num_left_str) >> num_left;
		std::istringstream(num_right_str) >> num_right;

		// ������������ ����� ����� ���������
		if (negative) num_left *= -1; // ������ �������������
		do
		{
			remainder = num_left % 16; // ������� 
			num_left = num_left / 16; // ��������� ����� ��� �������
			hexadecimalFraction_num_left += dictionary[remainder];

		} while (num_left != 0);

		// ������������ ������ ����� ���������
		num_right_str = "0," + std::to_string(num_right);
		double num_right_double = std::stod(num_right_str);

		while (true)
		{
			num_right_double *= 16;
			num_right_str = std::to_string(num_right_double);

			string t = ""; // ����� ����� �������
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
			// ������� ���������
			if (stoi(t) == 0) break;
		}

		/// ������ ������
		if (negative) hexadecimal = "-"; else hexadecimal = "";
		for (int i = hexadecimalFraction_num_left.size(); i > -1; i--)
			hexadecimal += hexadecimalFraction_num_left[i];

		/// ��������� ���������������
		hexadecimal += "." + hexadecimalFraction_num_right;
		cout << "�����������������: " << hexadecimal << endl;
		system("pause");
		system("cls");
	}
}

bool Convert::check_correct_input_hex(bool& negative, int& comma, string& num)
{
	// ��������� �����
	bool correct_input = false;
	int i = 0;
	if (negative) i = 1; // ���������� �����
	char	dictionary[16] = { '0','1','2','3', '4','5','6','7','8','9','A','B','C','D','E','F' };
	int counter = 0;
	for (; i < num.size(); i++)
	{
		if (num[i] == '.' || num[i] == ',') comma++;
		if (comma > 1) // ���� ������� ������ 1
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
	cout << "� ����� ������� ��������� ��������� �����?" << endl
		<< "1. ��������" << endl
		<< "2. ����������" << endl
		<< "�����: ";
	cin >> choice;
	system("cls");
}

void Convert::convert_16_to_10(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional, int& fractional_num)
{
	/*
	* -----------------------------------------------
	*  ������������ � ���������� �������
	* -----------------------------------------------
	*/

	if (comma == 0) // ���� ��������� �����
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
	else // ���� ����� �������
	{
		// ��������� ������� ����� ����� �������
		for (int i = 0; i < num.size(); i++)
			if (num[i] == '.' || num[i] == ',')
			{
				fractional_num = (num.size() - i) - 1;
				break;
			}

		// ����� �����
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

		// ������ �����

		// ������� �����������
		//auto pos = num.find('.');
		//if (pos != std::string::npos) num.erase(pos, 1);
		//pos = num.find(',');
		//if (pos != std::string::npos) num.erase(pos, 1);

		// ������������
		for (int i = num.size(); i > -1; i--)
		{
			double pow = 1;
			int deg = (int)(num.size() - (i + 1 + fractional_num));

			if (deg < 0) { // ���� ������� �������������
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
	* ������������ � �������� �����
	* -----------------------------------------------
	*/

	string binary = ""; // �����
	string binary_fractional = ""; // �������
	int fractional_num = 0; // ����� ����� �������
	int remainder = 0;

	if (comma == 0) // ���� ��������� �����
	{
		// ������������ ���������
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 2; // ������� 
			decimal = decimal / 2; // ��������� ����� ��� �������
			binary += to_string(remainder);
		} while (decimal != 0);

		// ������ ������
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}
	else // ���� ��������� �������
	{
		/// ����� �����
		if (negative) decimal *= -1; // ������ �������������
		do
		{
			remainder = decimal % 2; // ������� 
			decimal = decimal / 2; // ��������� ����� ��� �������
			binary += to_string(remainder);
		} while (decimal != 0);

		/// ������ �����
		string num_right_str = "";
		if (negative) decimal_fractional *= -1.0;
		while (true)
		{
			decimal_fractional *= 2;
			num_right_str = std::to_string(decimal_fractional);

			string t = ""; // ����� ����� �������
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
			// ������� ���������
			if (stoi(t) == 0) break;
		}

		/// ������ ����� �����			
		string temp_binary = "";
		if (negative) temp_binary = "-"; else temp_binary = "";
		for (int i = binary.size(); i > -1; i--)
			temp_binary += binary[i];
		binary = temp_binary;
	}

	/// ��������� ���������������
	if (comma == 0) // ���� ��������� �����
	{
		cout << "��������: " << binary << endl;
		system("pause");
		system("cls");
	}
	else if (comma > 0) // ���� ��������� �������
	{
		binary += "." + binary_fractional;
		cout << "��������: " << binary << endl;
		system("pause");
		system("cls");
	}
}