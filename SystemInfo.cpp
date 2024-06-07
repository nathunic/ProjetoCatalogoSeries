/*
 * SysInfo.cpp
 *
 *  Created on: Abr, 2024
 *      Author: andre (houve uma pequena modificacao pelo grupo)
 */

#include "SystemInfo.h"

const string SysInfo::author = "Fabio Santos, Giovana Andrade, Guilherme Faitarone, Nathalia Ricardo e Nicolas Cardia";
const string SysInfo::date = "Junho, 2024";
const string SysInfo::department = "Faculdade de Tecnologia - Limeira/SP";
const string SysInfo::institution = "Universidade Estadual de Campinas (Unicamp)";
const string SysInfo::systemName = "Projeto Catalogo de Series FGN";
const string SysInfo::version = "0.01";
const string SysInfo::helpFile = "CatSeriesFGN.txt";

const string& SysInfo::getAuthor(){
	return author;
}

const string& SysInfo::getDate(){
	return date;
}

const string& SysInfo::getDepartment(){
	return department;
}

const string& SysInfo::getInstitution(){
	return institution;
}

const string& SysInfo::getSystemName(){
	return systemName;
}

const string& SysInfo::getVersion(){
	return version;
}

const string& SysInfo::getHelpFile(){
	return helpFile;
}

const string SysInfo::getFullVersion(){
	return systemName + " | Versao " + version + " (" + date + ")";
}
