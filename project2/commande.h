#pragma once
#include <string>
#include <vector>
#include "produit.h"
using namespace std;
class commande
{
	
	string date;
	
	
public:
	vector<produit> v;
	~commande() {};

	
	void setdate();


	string getdate();
	

};


