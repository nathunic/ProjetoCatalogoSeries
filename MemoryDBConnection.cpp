/*
 * MemoryDBConnection.cpp
 *
 *  Created on: Mar 22, 2024
 *      Author: andre (houve uma pequena modificacao pelo grupo)
 */

#include "MemoryDBConnection.h"

using namespace std;

MemoryDBConnection::MemoryDBConnection()
{
	registersDB = vector<Register*>();
}

MemoryDBConnection::~MemoryDBConnection()
{
	close();
}

vector<Register*>& MemoryDBConnection::getRegisterList()
{
	return registersDB;
}

void MemoryDBConnection::close()
{

	for (Register *buffer : registersDB)
	{
		delete buffer;
		buffer = NULL;
	}

	registersDB.clear();
}

