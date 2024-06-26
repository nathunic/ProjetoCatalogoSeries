/*
 * Utils.cpp
 *
 *  Created on: Abr, 2024
 *      Author: andre (houve uma pequena modificacao pelo grupo)
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Utils.h"
#include "SystemInfo.h"

 void Utils::printMessage(string text){
	cout << "* " << text << " *" << "\n" << endl;
}

void Utils::printFramedMessage(string text, string symbol, int length){
	cout << replicate(symbol,length) << endl;;
	cout << text << endl;
	cout << replicate(symbol,length) << endl;;
}

string Utils::replicate(string text, int times){
	string buffer;
	for (int count = 0; count < times; count++){
		buffer += text;
	}
	return (buffer);
}

string Utils::formatString(string str, int width) {
    ostringstream oss;
    oss << left << setw(width) << str; //manipula a formatação da string
    return oss.str();
}

string Utils::formatInt(int num, int width) {
    ostringstream oss;
    oss << left << setw(width) << num;
    return oss.str();
}
