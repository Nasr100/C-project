#pragma once

#include <string>
#include <iostream>
#include "commande.h"
using namespace std;
class client
{
	static int cnt;
	int id;
	string nom;
	string mdp;
	commande c;
public:
	
	~client() {};
	
	int static getcnt();
	static void setcnt(int n);
	
	int getid() {
		
		return this->id;
	}
	void setId();
	void setNom(string N);
	string getnom() {
		return this->nom;
	}
	string getmdp(){
		return this->mdp;
	};
	void setmdp(string MDP);

	
	void affiche();
//	void nvClient();
};



