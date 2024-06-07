/*
 * Controller.h
 *
 *  Created on: Jun, 2024
 *      Authors: fabio, guilherme, giovana, nathalia, nicolas
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <string>
#include <vector>

#include "MemoryDBConnection.h"
#include "Register.h"
#include "AbstractRegisterDAO.h"
#include "RegisterMemDAO.h"

using namespace std;

class Controller final {

	private:
		MemoryDBConnection *memoryDBConnection;
		AbstractRegisterDAO *regMemDAO;

		void actionSeries(void);		//ações da opção series
		void actionRelatorios(void);	//ações da opção relatorios
		void actionHelp(void);			//ações da opção ajuda
		void actionAbout(void);		//ações da opção créditos
		void launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions);

		void newRegister(void); 		//Adicionar novo registro
		void recoverRegister(void); 	//Recuperar um registro
		void editRegister(void); 		//Editar um registro
		void deleteRegister(void);	 	//Deletar um registro

		void orderbyTitle(void); 		//Ordenar por título 
		void orderByNetwork(void);		//Ordenar por streaming
		void orderByYear(void);			//Ordernar por ano
		void orderByRating(void);		//Ordenar por classificação

		void showOneRegister(Register *reg); // Exibir um registro
		void returnMenu(string message); //Função que retorna ao menu anterior e limpa a tela
		bool isNumber(string text);

		// Método de exibição da lista de registros
    	void display(Register *reg);
    	static void displayHeader(); // Cabeçalho da tabela

	public:
		Controller();
		virtual ~Controller();
		void start();
	};

#endif /* CONTROLLER_H_ */
