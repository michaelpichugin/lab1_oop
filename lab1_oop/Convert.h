#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Convert
{
public:
	Convert();
private:
	void input_num(string& num);
	void menu_1(unsigned int& choice);
	void menu_1_1(unsigned int& choice);
	bool check_correct_input_binary(bool& negative, int& comma, string& num);
	void convert_2_to_10(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional, int& fractional_num);
	void convert_2_to_16(bool& negative, int& comma, int& decimal, double& decimal_fractional);
	void menu_2(unsigned int& choice);
	bool check_correct_input_decimal(bool& negative, int& comma, string& num);
	void convert_10_to_2(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional);
	void convert_10_to_16(bool& negative, int& comma, string& num, int& decimal);
	bool check_correct_input_hex(bool& negative, int& comma, string& num);
	void menu_3(unsigned int& choice);
	void convert_16_to_10(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional, int& fractional_num);
	void convert_16_to_2(bool& negative, int& comma, string& num, int& decimal, double& decimal_fractional);
	bool work;
	string num; // ¬веденное число
	unsigned int choice; // ƒл€ выбора
};

