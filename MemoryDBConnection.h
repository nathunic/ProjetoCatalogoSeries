/*
 * MemoryDBConnection.h
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#ifndef MEMORYDBCONNECTION_H_
#define MEMORYDBCONNECTION_H_

#include <vector>

#include "Register.h"

using namespace std;

class MemoryDBConnection
	{
	private:
		vector<Register*> registersDB;

	public:
		MemoryDBConnection();
		virtual ~MemoryDBConnection();

		vector<Register*>& getRegisterList();
		void close();
	};

#endif /* MEMORYDBCONNECTION_H_ */
