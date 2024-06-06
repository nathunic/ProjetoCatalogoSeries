/*
 * RegisterMemDAo.cpp
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


#include "RegisterMemDAO.h"


RegisterMemDAO::RegisterMemDAO(MemoryDBConnection *memoryDBConnection) : memoryDBConnection(memoryDBConnection){
}

RegisterMemDAO::~RegisterMemDAO(){
	// TODO Auto-generated destructor stub
}


vector<Register*>& RegisterMemDAO::getAllRegisters(){
	return (memoryDBConnection->getRegisterList());
}


Register* RegisterMemDAO::getRegisterById(int registerId){
	vector<Register*> &registros = memoryDBConnection->getRegisterList();
	vector<Register*>::iterator registrosIterator = registros.begin();
	Register *buffer = NULL;
	bool found = false;

	while ((!found) && (registrosIterator != registros.end()))
	{
		if ((*registrosIterator)->getRegisterId() == registerId){
			found = true;
			buffer = *registrosIterator;
		}
		registrosIterator++;
	}

	return (buffer);
}


void RegisterMemDAO::addRegister(Register *reg){
	//reg->setRegisterId(++lastRegisterId);
	(memoryDBConnection->getRegisterList()).push_back(reg);
}

void RegisterMemDAO::updateRegister(Register *reg){
	deleteRegister(reg->getRegisterId());
	addRegister(reg);
}

void RegisterMemDAO::deleteRegister(int registerId){
	vector<Register*> &regs = memoryDBConnection->getRegisterList();
	vector<Register*>::iterator regsIterator = regs.begin();
	bool found = false;

	while ((!found) && (regsIterator != regs.end())){
		if ((*regsIterator)->getRegisterId() == registerId){
			found = true;
			delete *regsIterator;
			regs.erase(regsIterator);
		}
		regsIterator++;
	}
}


bool RegisterMemDAO::compareRegisterByTitle(Register *reg1, Register *reg2){
	return ((transformToUpper(reg1->getRegisterName())) < (transformToUpper(reg2->getRegisterName())));
}

bool RegisterMemDAO::compareRegisterByNetwork(Register *reg1, Register *reg2){
	return (transformToUpper((reg1->getNetwork())) < transformToUpper((reg2->getNetwork())));
}

bool RegisterMemDAO::compareRegisterByYear(Register *reg1, Register *reg2){
	return ((reg1->getReleaseYear()) > (reg2->getReleaseYear()));
}

bool RegisterMemDAO::compareRegisterByRating(Register *reg1, Register *reg2){
	return ((reg1->getRating()) > (reg2->getRating()));
}



void RegisterMemDAO::orderByTitle(){
	sort(memoryDBConnection->getRegisterList().begin(), memoryDBConnection->getRegisterList().end(), compareRegisterByTitle);
}

void RegisterMemDAO::orderByNetwork(){
	sort(memoryDBConnection->getRegisterList().begin(), memoryDBConnection->getRegisterList().end(), compareRegisterByNetwork);
}

void RegisterMemDAO::orderByYear(){
	sort(memoryDBConnection->getRegisterList().begin(), memoryDBConnection->getRegisterList().end(), compareRegisterByYear);
}

void RegisterMemDAO::orderByRating(){
	sort(memoryDBConnection->getRegisterList().begin(), memoryDBConnection->getRegisterList().end(), compareRegisterByRating);
}


string RegisterMemDAO::transformToUpper(string text){
	transform(text.begin(), text.end(), text.begin(), ::toupper);
	return text;
}
