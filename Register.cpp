/*
 * User.cpp
 *
 *  Created on: Mar 22, 2024
 *      Author: andre
 */

#include "Register.h"

int Register::lastRegisterId = 0;



Register::Register(string registerName, int releaseYear, int season, int numEpisodes,
				   string mainActors, string mainCharacters, string network, int rating):
		registerName(registerName), releaseYear(releaseYear), season(season), numEpisodes(numEpisodes),
		mainActors(mainActors),	mainCharacters (mainCharacters), network(network), rating(rating){
	
	this->registerId = ++lastRegisterId;		
}

Register::Register(int registerId, string registerName, int releaseYear, int season, int numEpisodes,
				   string mainActors, string mainCharacters, string network, int rating):
		registerId(registerId), registerName(registerName), releaseYear(releaseYear), season(season), numEpisodes(numEpisodes),
		mainActors(mainActors),	mainCharacters (mainCharacters), network(network), rating(rating){
}

Register:: ~Register()
{
	// TODO Auto-generated destructor stub
}

int Register::getRegisterId() const
{
	return registerId;
}

string Register::getRegisterName() const
{
	return registerName;
}
	
int Register::getReleaseYear() const
{
	return releaseYear;
}

int Register::getSeason() const
{
	return season;
}

int Register::getNumEpisodes() const
{
	return numEpisodes;
}

string Register::getMainActors() const
{
	return mainActors;
}

string Register::getMainCharacters() const
{
	return mainCharacters;
}

string Register::getNetwork() const
{
	return network;
}

int Register::getRating() const
{
	return rating;
}


