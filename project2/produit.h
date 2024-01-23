#pragma once

#include<string>
using namespace std;
class produit
{
//	static int cnt;
	//int id;
	string nomProduit;
	double prixUnitaire;
	int qteStock;
	
public :
	poduit(){
	}
	~produit() {};
	//void setid(int cnt);
	void setnomProduit(string N);
	void setprixUnitaire(double P);
	void setqteStock(int S);

	//int getid();
	string getnomProduit();
	double getprixUnitair();
	int getqteStock();

	void affiche();
	void produitToText();





};

