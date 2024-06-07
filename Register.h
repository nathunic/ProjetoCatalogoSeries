/*
 * User.h
 *
 *  Created on: Jun, 2024
 *      Author: guilherme
 */

#ifndef USER_H_
#define USER_H_

#include <string>

using namespace std;

class Register
	{
	private:
		static int lastRegisterId;
		int registerId;
		string registerName;
		int releaseYear;
		int season;
		int numEpisodes;
		string mainActors;
		string mainCharacters;
		string network;
		int rating; 


	public:
		Register(string registerName, int releaseYear, int season, int numEpisodes, string mainActors, string mainCharacters, string network, int rating);
		Register(int registerId, string registerName, int releaseYear, int season, int numEpisodes, string mainActors, string mainCharacters, string network, int rating);
		virtual ~Register();

		int getRegisterId() const;
		string getRegisterName() const;
		int getReleaseYear() const;
		int getSeason() const;
		int getNumEpisodes() const;
		string getMainActors() const;
		string getMainCharacters() const;
		string getNetwork() const;
		int getRating() const;
	};

#endif
