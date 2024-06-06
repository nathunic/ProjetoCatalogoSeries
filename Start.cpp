/*
 * Start.cpp
 *
 *  Created on: Abr, 2024
 *      Author: XXXXX
 */

#include <string>
#include <exception>
#include <memory>

#include "Controller.h"
#include "SystemInfo.h"
#include "Utils.h"

using namespace std;

int main(int argc, char *argv[]){

	try{
		(make_unique<Controller>())->start();
	}
	catch (const exception &myException){
		Utils::printMessage("Ocorreu um erro inesperado e o programa foi encerrado. " + string(myException.what()));
		exit(1);
	}

	return (0);
}

