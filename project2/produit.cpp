#include "produit.h"
#include<iostream>
#include <string>
using namespace std;

//int produit::cnt = 0;
//void produit::setid(int cnt){
//
////{		produit::cnt=cnt++;
//		this->id = cnt;
//}

void produit::setnomProduit(string N)
{
	nomProduit = N;
}

void produit::setprixUnitaire(double P)
{
	this->prixUnitaire = P;
}

void produit::setqteStock(int S)
{
	this->qteStock = S;
}

//int produit::getid()
//{
//	return this->id;
//}

string produit::getnomProduit()
{
	return this->nomProduit;
}
double  produit::getprixUnitair()
{
	return this->prixUnitaire;
}

int produit::getqteStock()
{
	return this->qteStock;
}

//void produit::affiche()
//{
//	cout << produit::getid() << " : " << produit::getnomProduit() << " : " << produit::getprixUnitair() << " : " << produit::getqteStock() << endl;
//}





