#include "client.h"

int client:: getcnt() {
	return client::cnt;
}
void client:: setcnt(int n) {
	cnt = n;
}

void client::setNom(string N)
{	
	this->nom = N;
} 

void client::setId()
{
	client::cnt++;
	this->id = cnt;
}
void client::setmdp(string MDP){
	this->mdp=MDP;
	}
void client::affiche()
{
	cout << client::getid() <<" : " << client::getnom() << endl;
}

int client::cnt = 0;


