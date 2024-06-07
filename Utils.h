/*
 * Utils.h
 *
 *  Created on: Abr, 2024
 *      Author: andre (houve uma pequena modificacao pelo grupo)
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

using namespace std;

class Utils final{
	public:
		static void printMessage(string text);
		static void printFramedMessage(string text, string symbol, int length);
		static string replicate(string text, int times);

		//Esses métodos definem a largura e a justificação dos valores
		static string formatString(string str, int width);
		static string formatInt(int num, int width);
};
#endif /* UTILS_H_ */