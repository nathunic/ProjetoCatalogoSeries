/*
 * RegisterMemDAo.h
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#ifndef REGISTERMEMDAO_H_
#define REGISTERMEMDAO_H_

#include "AbstractRegisterDAO.h"
#include "MemoryDBConnection.h"

class RegisterMemDAO: public AbstractRegisterDAO{
	private:
		MemoryDBConnection* memoryDBConnection;
		static int lastRegisterId;
		static bool compareRegisterByTitle(Register *reg1, Register *reg2);
		static bool compareRegisterByNetwork(Register *reg1, Register *reg2);
		static bool compareRegisterByYear(Register *reg1, Register *reg2);
		static bool compareRegisterByRating(Register *reg1, Register *reg2);
		static string transformToUpper(string text);

	public:
		RegisterMemDAO(MemoryDBConnection* memoryDBConnection);
		virtual ~RegisterMemDAO();

		virtual vector<Register*>& getAllRegisters();
		virtual Register* getRegisterById(int registerId);
		virtual void addRegister(Register *reg);
		virtual void updateRegister(Register *reg);
		virtual void deleteRegister(int registerId);

		void orderByTitle();
		void orderByNetwork();
		void orderByYear();
		void orderByRating();
	};

#endif /* REGISTERMEMDAO_H_ */
