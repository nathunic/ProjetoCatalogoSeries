/*
 * Controller.cpp
 *
 *  Created on: Jun, 2024
 *      Authors: fabio, guilherme, giovana, nathalia, nicolas
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

//Mensagens de erro
constexpr const char* ERR_NOREGISTER = "Lista de registros vazia. O sistema ira retornar ao menu.";
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


//métodos relacionados a funcionalidade do menu e sub-menu
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
	Utils::printFramedMessage(file->getFileContent(), "-", 120);
	
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
	Utils::printFramedMessage(text, "-", 120);

	returnMenu(MSG_RETURN);
}

//método que gerencia o menu
void Controller::launchActions(string title, vector<string> menuItens, vector<void (Controller::*)()> functions){
	try {
		Menu menu(menuItens, title, "\nSelecione a opcao desejada: ");
		menu.setSymbol("-");

		while (int choice = menu.getChoice()){
			(this->*functions.at(choice - 1))();
		}

	}
	catch (const exception &myException){
		Utils::printMessage("Ocorreu um erro inesperado " + string(myException.what()));
	}
}


//método que exibe apenas um registro na tela
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


//métodos relacionados a exibição de um ou mais registros - são usados nos relatorios
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

//método que exibe uma mensagem da tela e aguarda o usuário clicar em enter para retornar ao menu
void Controller::returnMenu(string message){
	string entry;
	cout << "\n" << message;
	getline(cin, entry);
	system("cls");
}

//função que retorna se uma string tem apenas números
bool Controller::isNumber(string text) {
    for (char const &ch : text) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}


//método que insere o registro na mémoria
//a função stoi: Converte uma string para int
void Controller::newRegister(void){
	string name, mainActors, mainCharacters, network, entry;
	int releaseYear, season, numEpisodes, rating;

	Utils::printMessage("NOVO REGISTRO DE SERIE");
	try{
		
		cout << "Nome da serie ..................................................: ";
		getline(cin, name);

		cout << "Ano de lancamento (AAAA) .......................................: ";
		getline(cin, entry);
		if (isNumber(entry)) //chama a função para validar se foi digitado apenas números
			releaseYear = std::stoi(entry); //se foi contém apenas números faz a conversão da string para inteiro e guarda na variável correspondente
		else
			throw invalid_argument(ERR_INT); //senão, lança uma mensagem de erro e cancela a inserção

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
		getline(cin, mainActors);

		cout << "Personagens principais (nomes separados por virgula) ...........: ";
		getline(cin, mainCharacters);

		cout << "Nome do canal/streaming ........................................: ";
		getline(cin, network);

		cout << "Classificacao (0-10) ...........................................: ";
		getline(cin, entry);
		if (isNumber(entry)){
			rating = std::stoi(entry);
			if(!(rating >= 0) || !(rating <= 10)) //valida se o número informado está entre 0 e 10
				throw invalid_argument("Valor invalido. Valor deve ser entre 0 e 10. Tente novamente.");
		}
		else
			throw invalid_argument(ERR_INT);

		cout << "(S) para confirmar e (N) para cancelar: ";
		getline(cin, entry);

		if (toupper(entry.at(0)) == 'S'){
			regMemDAO->addRegister(new Register(name, releaseYear, season, numEpisodes, mainActors, mainCharacters, network, rating)); //chama o método da classe RegisterMemDAO que faz a inserção do registro na memória
			cout << "\n";
			Utils::printMessage("Novo registro de serie incluido com sucesso.");
			returnMenu(MSG_RETURN); //chama o método para retornar ao menu
		} else{
			throw invalid_argument("Acao cancelada."); // se o usuário digitou qualquer coisa diferente de 's' ou 'S', o sistema lança um erro de exceção
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
				showOneRegister(recRegister); //chama o método que exibe apenas um registro
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
					showOneRegister(oldRegister); //exibe os dados do registro antes da alteração
					
					cout << "DADOS NOVOS (Digite <Enter> se nao deseja alterar): " << endl;
					cout << "Nome da serie .........................: ";
					getline(cin, name);
					
					cout << "Ano de lancamento (AAAA) ..............: ";
					getline(cin, entry);
					if (entry.empty()) //se o usuário não digitou nada, significa que não deseja alterar esse campo
						releaseYear = oldRegister->getReleaseYear(); //então, o sistema irá assumir o valor antigo
					else
						if(isNumber(entry)) //chama a função para validar se foi digitado apenas números
							releaseYear = std::stoi(entry); //se contém apenas números faz a conversão da string para inteiro e guarda na variável correspondente
					else
						throw invalid_argument(ERR_INT); //senão, lança uma mensagem de erro e cancela a inserção
					
					cout << "Temporada (Apenas numeros) ............: ";
					getline(cin, entry);
					if (entry.empty())
						season = oldRegister->getSeason();
					else
						if(isNumber(entry))
							season = std::stoi(entry);
					else
						throw invalid_argument(ERR_INT);

					cout << "Numero de episodios (Apenas numeros) ..: ";
					getline(cin, entry);
					if (entry.empty())
						numEpisodes = oldRegister->getNumEpisodes();
					else 
						if(isNumber(entry))
							numEpisodes = std::stoi(entry);
					else
						throw invalid_argument(ERR_INT);

					cout << "Atores principais .....................: ";
					getline(cin, mainActors);
					
					cout << "Personagens principais ................: ";
					getline(cin, mainCharacters);
					
					cout << "Canal/Streaming .......................: ";
					getline(cin, network);
					
					cout << "Classificacao (0-10) ..................: ";
					getline(cin, entry);
					if (entry.empty())
						rating = oldRegister->getRating();
					else{
						if(isNumber(entry)){
							rating = std::stoi(entry);
							if(!(rating >= 0) || !(rating <= 10))
								throw invalid_argument("Valor invalido. Valor deve ser entre 0 e 10. Tente novamente.");
						}
						else throw invalid_argument(ERR_INT);
					}

					cout << "(S) para confirmar; (N) para cancelar: ";
					getline(cin, entry);

					if (toupper(entry.at(0)) == 'S'){
						//valida que se o usuário informou algum dado nos campos de nome, atores principais, personagens principais e streaming
						name = (name.empty()) ? oldRegister->getRegisterName() : name;
						mainActors = (mainActors.empty()) ? oldRegister->getMainActors() : mainActors;
						mainCharacters = (mainCharacters.empty()) ? oldRegister->getMainCharacters() : mainCharacters;
						network = (network.empty()) ? oldRegister->getNetwork() : network;

						Register *newRegister = new Register(oldRegister->getRegisterId(), name, releaseYear, season, numEpisodes, mainActors, mainCharacters, network, rating); //cria uma nova instância de registro
						regMemDAO->updateRegister(newRegister);//chama o método de alteração da classe RegisterMemDAO

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
				cout << "O registro que voce deseja cancelar eh: " << endl;
				showOneRegister(oldRegister);//exibe os dados do registro a ser deletado para confirmação
				cout << "(S) para confirmar e (N) para cancelar:";
				getline(cin, answer);

				if (toupper(answer.at(0)) == 'S'){
					regMemDAO->deleteRegister(regId);
				}

				cout << "\n";
				Utils::printMessage("Registro deletado com sucesso.");
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



//métodos de ordenação
void Controller::orderbyTitle(void){

	Utils::printMessage("REGISTROS ORDENADOS POR NOME");
	string entry;

	if (!regMemDAO->getAllRegisters().empty()){
		regMemDAO->orderByTitle();
		displayHeader();
		for (Register *buffer : (regMemDAO->getAllRegisters())){
			display(buffer);
		}
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
		for (Register *buffer : (regMemDAO->getAllRegisters())) {
			display(buffer);
		}		
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
		for (Register *buffer : (regMemDAO->getAllRegisters())) {
			display(buffer);
		}
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
		for (Register *buffer : (regMemDAO->getAllRegisters())) {
			display(buffer);
		}
	}
	else{
		Utils::printMessage(ERR_NOREGISTER);
	}

	returnMenu(MSG_RETURN);
}