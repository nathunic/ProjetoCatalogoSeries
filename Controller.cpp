/*
 * Controller.cpp
 *
 *  Created on: Abr, 2024
 *      Author: XXXXX
 */

#include <iostream>
#include <iomanip>
#include <memory>
#include <exception>
#include <cctype>
#include <algorithm>
#include <stdexcept>

#include "Controller.h"
#include "Menu.h"
#include "Utils.h"
#include "SystemInfo.h"
#include "TextFromFile.h"

using namespace std;
constexpr const char* ERR_NOREGISTER = "Lista de registros vazia. O sistema ira retornar ao menu anterior.";
constexpr const char* ERR_INT = "Valor informado deve ser apenas numeros. Tente novamente";
constexpr const char* MSG_RETURN = "Para retornar clique no botao <Enter>";

Controller::Controller(){
	memoryDBConnection = NULL;
	regMemDAO = new RegisterMemDAO(new MemoryDBConnection());
}

Controller::~Controller(){
	delete memoryDBConnection;
	memoryDBConnection = NULL;
}



void Controller::start(){
	vector<string> menuItens { "Series", "Relatorios", "Ajuda", "Creditos", "Sair" };
	vector<void (Controller::*)()> functions { &Controller::actionSeries, &Controller::actionRelatorios, &Controller::actionHelp, &Controller::actionAbout};
	launchActions("Menu Principal", menuItens, functions);
}

void Controller::actionSeries(void){
	vector<string> menuItens{ "Incluir", "Recuperar", "Editar", "Excluir", "Retornar" };
	vector<void (Controller::*)()> functions{ &Controller::newRegister, &Controller::recoverRegister, &Controller::editRegister, &Controller::deleteRegister };
	launchActions("Series", menuItens, functions);
}

void Controller::actionRelatorios(void){
	vector<string> menuItens{ "Registros ordenados por titulo", "Registros ordenados por canal/network", "Registros ordenados por ano", "Registros ordenados por nota", "Retornar" };
	vector<void (Controller::*)()> functions{ &Controller::orderbyTitle, &Controller::orderByNetwork, &Controller::orderByYear, &Controller::orderByRating };
	launchActions("Relatorios", menuItens, functions);
}

void Controller::actionHelp(void){
	string entry;
	Utils::printMessage("Ajuda | " + SysInfo::getFullVersion());
	unique_ptr<TextFromFile> file (new TextFromFile(SysInfo::getHelpFile()));
	Utils::printFramedMessage(file->getFileContent(), "*", 120);
	
	returnMenu(MSG_RETURN);

}

void Controller::actionAbout(void){
	string entry;
	string text = "Sobre | ";
	text += SysInfo::getFullVersion() + "\n";
	text += SysInfo::getAuthor() + "\n";
	text += SysInfo::getInstitution() + "\n";
	text += SysInfo::getDepartment();
	Utils::printMessage(SysInfo::getVersion());
	Utils::printFramedMessage(text, "*", 120);

	returnMenu(MSG_RETURN);
}

void Controller::launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions){
	try {
		Menu menu(menuItens, title, "\nSelecione a opcao desejada: ");
		menu.setSymbol("*");

		while (int choice = menu.getChoice()){
			(this->*functions.at(choice - 1))();
		}

	}
	catch (const exception &myException){
		Utils::printMessage("Ocorreu um erro inesperado " + string(myException.what()));
	}
}


void Controller::showOneRegister(Register *reg){
	cout << "Nome da serie ..................: " << reg->getRegisterName() << endl;
	cout << "Ano de lancamento ..............: " << reg->getReleaseYear() << endl;
	cout << "Temporada ......................: " << reg->getSeason() << endl;
	cout << "Numero de episodios ............: " << reg->getNumEpisodes() << endl;
	cout << "Atores principais ..............: " << reg->getMainActors() << endl;
	cout << "Personagens principais .........: " << reg->getMainCharacters() << endl;
	cout << "Streaming ......................: " << reg->getNetwork() << endl;
	cout << "Classificacao (0-10) ...........: " << reg->getRating() << endl;
	cout << "\n" << endl;
}

void Controller::display(Register *reg){
	cout << Utils::formatInt(reg->getRegisterId(), 5) << Utils::formatString(reg->getRegisterName(), 30) << Utils::formatInt(reg->getReleaseYear(), 15)
         << Utils::formatInt(reg->getSeason(), 15) << Utils::formatInt(reg->getNumEpisodes(), 20) << Utils::formatString(reg->getMainActors(), 30)
         << Utils::formatString(reg->getMainCharacters(), 30) << Utils::formatString(reg->getNetwork(), 10)
         << Utils::formatInt(reg->getRating(), 10) << endl;
}

void Controller::displayHeader(){
	cout << Utils::formatString("ID", 5) << Utils::formatString("Nome da Serie", 30) << Utils::formatString("Lancamento", 15)
         << Utils::formatString("Temporada", 15) << Utils::formatString("Qtd Episodios", 20) << Utils::formatString("Principais Atores", 30)
         << Utils::formatString("Personagens Principais", 30) << Utils::formatString("Canal", 10)
         << Utils::formatString("Nota", 10) << endl;
    cout << string(165, '-') << endl;
}

void Controller::returnMenu(string message){
	string entry;
	cout << "\n" << message;
	getline(cin, entry);
	system("cls");
}

bool Controller::isNumber(string text) {
    for (char const &ch : text) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}



void Controller::newRegister(void){
	string name, mainActors, mainCharacters, network, entry;
	int releaseYear, season, numEpisodes, rating;

	Utils::printMessage("NOVO REGISTRO DE SERIE");
	try{
		
		cout << "Nome da serie ..................................................: ";
		getline(cin, name);

		cout << "Ano de lancamento (AAAA) .......................................: ";
		getline(cin, entry);
		if (isNumber(entry))
			releaseYear = std::stoi(entry); // Converte a string para int
		else
			throw invalid_argument(ERR_INT);

		cout << "Temporada (apenas numeros) .....................................: ";
		getline(cin, entry);
		if (isNumber(entry))
			season = std::stoi(entry);
		else
			throw invalid_argument(ERR_INT);

		cout << "Quantidade de episodios (apenas numeros) .......................: ";
		getline(cin, entry);
		if (isNumber(entry))
			numEpisodes = std::stoi(entry);
		else
			throw invalid_argument(ERR_INT);
		
		cout << "Atores principais (nomes separados por virgula) ................: ";
		cin >> mainActors;

		cout << "Personagens principais (nomes separados por virgula) ...........: ";
		cin >> mainCharacters;

		cout << "Nome do streaming ..............................................: ";
		cin >> network;

		cout << "Classificacao (0-10) ...........................................: ";
		getline(cin, entry);
		if (isNumber(entry))
			rating = std::stoi(entry);
		else
			throw invalid_argument(ERR_INT);

		cout << "(S) para confirmar e (N) para cancelar: ";
		getline(cin, entry);

		if (toupper(entry.at(0)) == 'S'){
			regMemDAO->addRegister(new Register(name, releaseYear, season, numEpisodes, mainActors, mainCharacters, network, rating));
			cout << "\n";
			Utils::printMessage("Novo registro de serie incluido com sucesso.");
			returnMenu(MSG_RETURN);
		} else{
			throw invalid_argument("Acao cancelada.");
		}
	}
	catch(const exception& e){
		returnMenu(string(e.what()) + "\n\n" + MSG_RETURN);
	}
}

void Controller::recoverRegister(void){

	int regId = 0;
	string entry;
	Utils::printMessage("RECUPERAR REGISTRO");
	if (!regMemDAO->getAllRegisters().empty()){

		cout << "Identificador do registro que deseja recuperar: ";
		cin >> regId;
		cin.ignore();

		if (regId > 0){
			Register *recRegister = regMemDAO->getRegisterById(regId);
			if (recRegister != NULL){
				showOneRegister(recRegister);
			}
			else {
				Utils::printMessage("Registro nao cadastrado.");
			}
		}
		else {
				cout << "\nValor invalido. Tente novamente." << endl;
		}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);	
}

void Controller::editRegister(void){

	int regId = 0;
	string entry;
	Utils::printMessage("EDITAR REGISTRO");
	try{
		if(!regMemDAO->getAllRegisters().empty()){
			cout << "Identificador do registro a ser editado: ";
			cin >> regId;
			cin.ignore();
			if (regId > 0){
				Register *oldRegister = regMemDAO->getRegisterById(regId);
				if (oldRegister != NULL){
					string name, mainActors, mainCharacters, network, entry;
					int releaseYear, season, numEpisodes, rating;
					
					cout << "DADOS ATUAIS:" << endl;
					showOneRegister(oldRegister);
					
					cout << "DADOS NOVOS (Digite <Enter> se não deseja alterar): " << endl;
					cout << "Nome da serie .........................: " << endl;
					getline(cin, name);
					
					cout << "Ano de lancamento (AAAA) ..............: " << endl;
					getline(cin, entry);
					if (entry.empty()) releaseYear = oldRegister->getReleaseYear();
					else if(isNumber(entry)) releaseYear = std::stoi(entry);
					else throw invalid_argument(ERR_INT);
					
					cout << "Temporada (Apenas numeros) ............: " << endl;
					getline(cin, entry);
					if (entry.empty()) season = oldRegister->getSeason();
					else if(isNumber(entry)) season = std::stoi(entry);
					else throw invalid_argument(ERR_INT);

					cout << "Numero de episodios (Apenas numeros) ..: " << endl;
					getline(cin, entry);
					if (entry.empty()) numEpisodes = oldRegister->getNumEpisodes();
					else if(isNumber(entry)) numEpisodes = std::stoi(entry);
					else throw invalid_argument(ERR_INT);

					cout << "Atores principais .....................: " << endl;
					getline(cin, mainActors);
					
					cout << "Personagens principais ................: " << endl;
					getline(cin, mainCharacters);
					
					cout << "Streaming .............................: " << endl;
					getline(cin, network);
					
					cout << "Classificacao (0-10) ..................: " << endl;
					getline(cin, entry);
					if (entry.empty()) rating = oldRegister->getRating();
					else if(isNumber(entry)) rating = std::stoi(entry);
					else throw invalid_argument(ERR_INT);

					cout << "(S) para confirmar; (N) para cancelar: ";
					getline(cin, entry);

					if (toupper(entry.at(0)) == 'S'){
						name = (name.empty()) ? oldRegister->getRegisterName() : name;
						mainActors = (mainActors.empty()) ? oldRegister->getMainActors() : mainActors;
						mainCharacters = (mainCharacters.empty()) ? oldRegister->getMainCharacters() : mainCharacters;
						network = (network.empty()) ? oldRegister->getNetwork() : network;

						Register *newRegister = new Register(oldRegister->getRegisterId(), name, releaseYear, season, numEpisodes, mainActors, mainCharacters, network, rating);
						regMemDAO->updateRegister(newRegister);

						cout << "\n";
						Utils::printMessage("Registro de serie editado com sucesso.");
					}
					else {
						throw invalid_argument("Acao cancelada.");
					}
				}
				else {
					Utils::printMessage("Registro nao cadastrado.");
				}
			}
			else {
				throw invalid_argument("Valor invalido. Tente novamente.");
			}
		}
		else{
			throw invalid_argument(ERR_NOREGISTER);
		}
	}
	catch(const exception& e){
		returnMenu(string(e.what()) + "\n\n" + MSG_RETURN);
	}

	returnMenu(MSG_RETURN);
}

void Controller::deleteRegister(void){

	int regId = 0;
	string entry;
	Utils::printMessage("DELETAR REGISTRO");

	if(!regMemDAO->getAllRegisters().empty()){

		cout << "Id do registro a ser deletado: ";
		cin >> regId;
		cin.ignore();

		if (regId > 0){
			Register *oldRegister = regMemDAO->getRegisterById(regId);
			if (oldRegister != NULL){
				string answer;
				cout << "O registro que voce deseja cancelar eh ..............: " << endl;
				showOneRegister(oldRegister);
				cout << "(S) para confirmar; (N) para cancelar:";
				getline(cin, answer);

				if (toupper(answer.at(0)) == 'S'){
					regMemDAO->deleteRegister(regId);
				}

				cout << "\n";
				Utils::printMessage("Registro deletado com sucesso.");
				returnMenu(MSG_RETURN);
			}
			else{
				Utils::printMessage("Registro nao cadastrado");
			}
		}
		else{
			cout << "Valor invalido. Tente novamente" << endl;
		}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}




void Controller::orderbyTitle(void){

	Utils::printMessage("REGISTROS ORDENADOS POR NOME");
	string entry;

	if (!regMemDAO->getAllRegisters().empty()){
		regMemDAO->orderByTitle();
		displayHeader();
		for (Register *buffer : (regMemDAO->getAllRegisters())) {display(buffer);}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}

void Controller::orderByNetwork(void){
	Utils::printMessage("REGISTROS ORDENADOS POR CANAL");
	string entry;

	if (!regMemDAO->getAllRegisters().empty()){
		regMemDAO->orderByNetwork();
		displayHeader();
		for (Register *buffer : (regMemDAO->getAllRegisters())) {display(buffer);}		
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}

void Controller::orderByYear(void){
	Utils::printMessage("REGISTROS ORDENADOS POR ANO DE LANCAMENTO");
	string entry;

	if (!regMemDAO->getAllRegisters().empty()){
		regMemDAO->orderByYear();
		displayHeader();
		for (Register *buffer : (regMemDAO->getAllRegisters())) {display(buffer);}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}

void Controller::orderByRating(void){
	Utils::printMessage("REGISTROS ORDENADOS POR CLASSIFICACAO");
	string entry;

	if (!regMemDAO->getAllRegisters().empty()){
		regMemDAO->orderByRating();
		displayHeader();
		for (Register *buffer : (regMemDAO->getAllRegisters())) {display(buffer);}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}

