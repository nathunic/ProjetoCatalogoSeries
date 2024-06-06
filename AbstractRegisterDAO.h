/*
 * AbstractRegisterDAO.h
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#ifndef ABSTRACTREGISTERDAO_H_
#define ABSTRACTREGISTERDAO_H_

#include "Register.h"
#include <vector>

using namespace std;

class AbstractRegisterDAO
	{
	public:
		AbstractRegisterDAO();
		virtual ~AbstractRegisterDAO();

		virtual vector<Register*>& getAllRegisters() = 0;
		virtual Register* getRegisterById(int registerId) = 0;
		virtual void addRegister(Register *reg) = 0;
		virtual void updateRegister(Register *reg) = 0;
		virtual void deleteRegister(int registerId) = 0;
		
		virtual void orderByTitle() = 0;
		virtual void orderByNetwork() = 0;
		virtual void orderByYear() = 0;
		virtual void orderByRating() = 0;
	};

#endif /* ABSTRACTREGISTERDAO_H_ */
