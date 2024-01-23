#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <sstream>
#include "client.h"
#include "produit.h"
#include "commande.h"
using namespace std;




char HOST[]="localhost";
char USER[]="root";
char PASS[]="nasr2003";
char DB[]="site";

client client1;
int id_session;
produit p1;
int main() {
	
	
	int choice=0;
	
	bool quit=false;
	
	string query;
	MYSQL *conn;
	if(!(conn = mysql_init(0)))
	{
		cout << "ERROR : MYSQL OBJECT COULD NOT BE CREATED."<<endl;
	}
	else
	{
		if(!mysql_real_connect(conn,HOST,USER,PASS,DB,3306,NULL,0))
		{
			cout<<"ERROR : some database info is wrong or do not exist"<<endl;
			cout<<mysql_error(conn)<<endl;
		}
		else
		{
			cout<<"logged in."<<endl;	
		}
		
	}
	
	do {
		system("cls");
		cout<<"$$$$$$$$----MENU-----$$$$$$$$$"<<endl;
		cout <<"\t1-create account\t"<<endl;
		cout <<"\t2-log in\t"<<endl;
		cout <<"\t3-log in as Admin\t"<<endl;
		cout <<"\t0-quitter\t"<<endl;
		cout<<"choisir : ";
		cin>>choice;
		
		switch (choice){
			
			case 1 :{
					system("cls");
					cout<<"$$$$$$$$----creer un client-----$$$$$$$$$"<<endl;
					string nom;
					string mdp;
					
					cout<<"entrez votre nom : ";
					cin>>nom;
					cout<<"entrez un mot de passe : ";
					cin >>mdp;
					client1.setNom(nom);
					client1.setmdp(mdp);
					query="INSERT INTO client(client_nom,client_mdp)VALUES('"+client1.getnom()+"','"+client1.getmdp()+"')";
					if(mysql_query(conn,query.c_str()))
					{
						cout<<mysql_error(conn)<<endl;
					}
					else
					{
						cout <<endl;
						cout<<" votre compte a ete cree avec succes!!"<<endl;
						
					}
					getch();
					
				break;
			}
			case 2:{
				string nom2;
				string mdp2;
				system("cls");
					cout<<"$$$$$$$$----login-----$$$$$$$$$"<<endl;
					cout<<"nom : ";
					cin >>nom2;
					cout<<"mot de passe : ";
					cin >>mdp2;
					query=" SELECT * FROM client WHERE client_nom = '"+nom2+"' && client_mdp ='"+mdp2+"' ";
						if(mysql_query(conn,query.c_str()))
					{	
						cout<<mysql_error(conn)<<endl;
					}
					else
					{
						MYSQL_RES* res;
						res=mysql_store_result(conn);
						if(res)
						{
							MYSQL_ROW row=mysql_fetch_row(res);
						if(row){
							int x=0;
							bool quit2=false;
							query="SELECT CLIENT_ID FROM client where client_nom='"+nom2+"' ";
							if(mysql_query(conn,query.c_str()))
							{	
							cout<<mysql_error(conn)<<endl;
							}
							else
							{
								MYSQL_RES* res;
								res=mysql_store_result(conn);
								if(res)
								{
								MYSQL_ROW row=mysql_fetch_row(res);
									if(row){
											id_session=atoi(row[0]);
									}
								}
							}
							
						
						do 
						{
						system("cls");
						cout<<"$$$$$$$$----Bienvenu-----$$$$$$$$$"<<endl;
						cout <<"\t1-afficher les produits\t"<<endl;
						cout <<"\t0-quitter\t"<<endl;
						cout<<"choisir : ";
						cin>>x;
							switch (x)
							{
								case 1:
								{
									system("cls");
									cout<<"$$$$$$$$----Afficher produit-----$$$$$$$$$"<<endl;
									query="SELECT * FROM produit";
									if(mysql_query(conn,query.c_str()))
										{
											cout<<mysql_error(conn)<<endl;
										}else
										{
											MYSQL_RES* res;
											res=mysql_store_result(conn);
											if(res)
											{
												int num=mysql_num_fields(res);
												MYSQL_ROW row;
												cout<<"\t\t ID\t\t qte\t\t nom\t\t prix unitaire"<<endl;
												cout<<"\t\t --\t\t ---\t\t ---\t\t -------------"<<endl;
												while(row=mysql_fetch_row(res)){
													for(int i=0;i<num;i++){
														cout<<"\t\t "<<row[i];
													}
													cout << endl;
												}
												mysql_free_result(res);
											}
										}
										string client_choix;
										int client_qte;
										char des='n';
										char cmd;
										int BD_qte;
										int CL_qte_prod;
										commande C1;
										C1.setdate();
										stringstream Sid;
										Sid<<id_session;
										string STR_id_session=Sid.str();
										int CL_id_cmd;
										int CL_id_prod;
										int p_unit;
										do{
												
											cout << "choisir un produit : ";
											cin >> client_choix ;
											cout << "quantite : ";
											cin >> client_qte;
											string check="SELECT qte_stock from produit where prod_nom = '"+client_choix+"'  ";
											if(mysql_query(conn,check.c_str()))
											{
											cout<<mysql_error(conn)<<endl;
											}
											else
											{
											MYSQL_RES* res;
											res=mysql_store_result(conn);
												if(res)
												{
													MYSQL_ROW row=mysql_fetch_row(res);
													if(row){
														BD_qte=atoi(row[0]);
													}
												}
											}
											if(BD_qte<client_qte){
												cout<<"quantite de produit en dtock est :  "<<BD_qte<<endl;
												cout << " nouvelle quantite : ";
												cin >> client_qte;
												
											}
											
												p1.setnomProduit(client_choix);
												p1.setqteStock(client_qte);
												C1.v.push_back(p1);
											
											cout<<"voulez vous choisir un autre produit ?(y or n)";
											cin >>des;
											
										
											
											
											
												
											
										}while(des == 'y');
										cout<<"voulez vous comfirme votre commande (y or n)";
										cin >>cmd;
										if(cmd=='y')
										{
											string check2="INSERT INTO commande (commande_date,cli_id)VALUES('"+C1.getdate()+"','"+STR_id_session+"')";
											if(mysql_query(conn,check2.c_str()))
											{
											cout<<mysql_error(conn)<<endl;
											}
											string check3="SELECT MAX(commande_ID) FROM commande where cli_id='"+STR_id_session+"' ";
											if(mysql_query(conn,check3.c_str()))
											{	
											cout<<mysql_error(conn)<<endl;
											}
											else
											{
												MYSQL_RES* res;
												res=mysql_store_result(conn);
												if(res)
												{
												MYSQL_ROW row=mysql_fetch_row(res);
													if(row){
															 CL_id_cmd=atoi(row[0]);
													}
												}
											}
											int sum=0;
											stringstream CL_Sid;
											CL_Sid<< CL_id_cmd;
											string STR_CL_id_cmd=CL_Sid.str();
											cout<<"\t FACTURE :\t"<<endl;
											cout<<"\t\t nom produit\t\t qte\t\t prix par produit"<<endl;
											cout<<"\t\t ----------  \t\t ---\t\t----------------"<<endl;
											
											for(int i=0;i<C1.v.size();i++)
											{
												int BD_qte;
												query="SELECT prod_id,qte_stock,prix_unitaire FROM PRODUIT WHERE prod_nom = '"+C1.v[i].getnomProduit()+"' ";
												if(mysql_query(conn,query.c_str()))
												{	
												cout<<mysql_error(conn)<<endl;
												}
												else
												{
														MYSQL_RES* res;
													res=mysql_store_result(conn);
													if(res)
													{
													MYSQL_ROW row=mysql_fetch_row(res);
														if(row)
														{
																 CL_id_prod=atoi(row[0]);
																 CL_qte_prod=atoi(row[1]);
																 p_unit=atoi(row[2]);
														}
													}
													
												}
												BD_qte=CL_qte_prod-C1.v[i].getqteStock();
												
												
												
												
											stringstream CL_Pid;
											CL_Pid<< CL_id_prod;
											string STR_CL_id_prod=CL_Pid.str();
											
											int CL_client_qte=C1.v[i].getqteStock();
											stringstream CL_Sqte;
											CL_Sqte<< CL_client_qte;
											string STR_CL_qte_prod=CL_Sqte.str();
											
												string newline="INSERT INTO ligne_commande VALUES('"+STR_id_session+"','"+STR_CL_id_cmd+"','"+STR_CL_id_prod+"','"+STR_CL_qte_prod+"')";
												if(mysql_query(conn,newline.c_str()))
												{	
												cout<<mysql_error(conn)<<endl;
												}
											
												stringstream STR_BD_qte;
												STR_BD_qte<< BD_qte;
												string STR_BD_qte_prod=STR_BD_qte.str();
												string update="UPDATE produit set qte_stock = '"+STR_BD_qte_prod+"'where prod_id='"+STR_CL_id_prod+"'";
												if(mysql_query(conn,update.c_str())){
													cout<<mysql_error(conn)<<endl;
												}
												
												
												cout<<"\t\t  "<<C1.v[i].getnomProduit()<<"\t\t  "<<C1.v[i].getqteStock()<<"\t\t       "<<p_unit*C1.v[i].getqteStock()<<endl;
												cout<<endl;
												sum=(p_unit*C1.v[i].getqteStock())+sum;
											}
											cout<<endl;
											cout<<"\t\t-----------------------------------------------\t\t"<<endl;
											cout<<endl;
											cout<<"\t\t Prix Totale a payer "<<"\t\t "<<sum<<endl;
											
										}
										
										
										
										getch();
									
									break;
								}
								case 0:
								{
									quit2=true;
									break;
								}
								default : 
								{
									system("cls");
									cout<<"choix invalide"<<endl;
									getch();
								
									break;
								}
								
							}
						}while(!quit2);
						
						
						}else
						{
							cout<<endl;
							cout<<"nom ou mot de passe invalide"<<endl;
								getch();
						}
						}
						
					break;
					}
					getch();
					}
			case 3:{
				string adminNom;
				string adminMdp;
				system("cls");
					cout<<"$$$$$$$$----ADMIN-----$$$$$$$$$"<<endl;
					cout<<"nom : ";
					cin >>adminNom;
					cout<<"mot de passe : ";
					cin >>adminMdp;
					query=" SELECT * FROM admin WHERE admin_nom = '"+adminNom+"' && admin_mdp ='"+adminMdp+"' ";
						if(mysql_query(conn,query.c_str()))
					{	
						cout<<mysql_error(conn)<<endl;
					}
					else
					{
						MYSQL_RES* res;
						res=mysql_store_result(conn);
						if(res)
						{
							MYSQL_ROW row=mysql_fetch_row(res);
							if(row)
							{
							int y=0;
							bool quit3=false;
						do 
						{
						system("cls");
						cout<<"$$$$$$$$----Bienvenu Admin-----$$$$$$$$$"<<endl;
						cout <<"\t1-ajouter un produit\t"<<endl;
						cout <<"\t2-Supprimer un produit\t"<<endl;
						cout <<"\t3-modifier un produit\t"<<endl;
						cout<<"\t4-Afficher tous les produits\t"<<endl;
						cout <<"\t0-quitter\t"<<endl;
						cout<<"choisir : ";
						cin>>y;
							switch (y)
							{
								case 1:
								{
									system("cls");
									cout<<"$$$$$$$$----ajouter produit -----$$$$$$$$$"<<endl;
									string nom_produit;
									double produit_pu;
									int qte;
									produit prod1;
									
									cout<<"entrez nom du produit : ";
									cin>>nom_produit;
									cout<<"entrez le prix unitaire : ";
									cin >>produit_pu;
									cout<<"entrez la quantite en stock : ";
									cin>>qte;
									prod1.setnomProduit(nom_produit);
									prod1.setprixUnitaire(produit_pu);
									prod1.setqteStock(qte);
									
									
									
									
									int prod_qte=prod1.getqteStock();
									stringstream sqte;
									sqte<<prod_qte;
									string strqte=sqte.str();
									
									double prod_pu=prod1.getprixUnitair();
									stringstream pu;
									pu<<prod_pu;
									string strpu=pu.str();
									
									query="INSERT INTO produit(qte_stock,prod_nom,prix_unitaire)VALUES('"+strqte+"','"+prod1.getnomProduit()+"','"+strpu+"')";
										if(mysql_query(conn,query.c_str()))
										{
											cout<<mysql_error(conn)<<endl;
										}
										else
										{
											cout<<"produit insere !!";
										}
										getch();
									break;
								}
								case 2:
								{
									system("cls");
									cout<<"$$$$$$$$----supprimer produit -----$$$$$$$$$"<<endl;
									string nom_prod;
									cout<<"entrer le nom de produit a supprimer : ";
									cin>>nom_prod;
									query="DELETE FROM produit WHERE prod_nom = '"+nom_prod+"' ";
									if(mysql_query(conn,query.c_str()))
										{
											cout<<mysql_error(conn)<<endl;
										}
										else
										{
											cout<<"produit supprimer!!"<<endl;	
										}
										getch();

									break;
								}
								case 3:
								{	
									int c=0;
									string P_nom;
									string nv_Nom;
									do 
									{
										system("cls");
										cout<<"$$$$$$$$----Modifier produit -----$$$$$$$$$"<<endl;
										cout <<"\t1-Modifier Nom produit\t"<<endl;
										cout <<"\t2-modifier Prix unitaire\t"<<endl;
										cout<<"\t3-modifier quantite de stock\t"<<endl;
										cout <<"\t0-quitter\t"<<endl;
										cout<<endl;
										cout<<"choisir : ";
										cin>>c;
										switch(c){
											case 1:
											{
												cout<<"$$$$$$$$----Modifier produit -----$$$$$$$$$"<<endl;
												cout<<endl;
												cout<<"entrez le nom de produit a Modifier : ";
												cin>>P_nom;
												cout<<"entrez un nouveau nom : ";
												cin>>nv_Nom;
												query="UPDATE produit set prod_nom = '"+nv_Nom+"' where prod_nom = '"+P_nom+"' ";
												if(mysql_query(conn,query.c_str()))
												{
													cout<<mysql_error(conn)<<endl;
												}
												else
												{
													cout<<"nom modifie!!"<<endl;	
												}
													getch();
													break;
											}
											case 2:
											{
												double price;
												cout<<"$$$$$$$$----Modifier produit -----$$$$$$$$$"<<endl;
												cout<<endl;
												cout<<"entrez le nom de produit a Modifier : ";
												cin>>P_nom;
												cout<<"entrez un nouveau prix : ";
												cin>>price;
												
												stringstream s_price;
												s_price<< price;
												string STR_price=s_price.str();
												
												
												
												query="UPDATE produit set prix_unitaire = '"+STR_price+"' where prod_nom = '"+P_nom+"' ";
												if(mysql_query(conn,query.c_str()))
												{
													cout<<mysql_error(conn)<<endl;
												}
												else
												{
													cout<<"prix modifie!!"<<endl;	
												}
													getch();
												
												
												break;
											}
											case 3:
											{
												int NV_QTE;
												cout<<"$$$$$$$$----Modifier produit -----$$$$$$$$$"<<endl;
												cout<<endl;
												cout<<"entrez le nom de produit a Modifier : ";
												cin>>P_nom;
												cout<<"entrez la nouvelle quantite en stock : ";
												cin>>NV_QTE;
												
												
												stringstream s_NV_QTE;
												s_NV_QTE<< NV_QTE;
												string STR_NV_QTE=s_NV_QTE.str();
												
												
												
												query="UPDATE produit set qte_stock = '"+STR_NV_QTE+"' where prod_nom = '"+P_nom+"' ";
												if(mysql_query(conn,query.c_str()))
												{
													cout<<mysql_error(conn)<<endl;
												}
												else
												{
													cout<<"prix modifie!!"<<endl;	
												}
													getch();
												
												
												break;
											}
											
										}
										
									
										
										
									}while(c!=0);
									getch();
									break;
								}
								case 4:
								{
									system("cls");
									cout<<"$$$$$$$$----Afficher produit -----$$$$$$$$$"<<endl;
									query="SELECT * FROM produit";
									if(mysql_query(conn,query.c_str()))
										{
											cout<<mysql_error(conn)<<endl;
										}else
										{
											MYSQL_RES* res;
											res=mysql_store_result(conn);
											if(res)
											{
												int num=mysql_num_fields(res);
												MYSQL_ROW row;
												cout<<"\t\t ID\t\t qte\t\t nom\t\t prix unitaire"<<endl;
												cout<<"\t\t --\t\t ---\t\t ---\t\t -------------"<<endl;
												while(row=mysql_fetch_row(res)){
													for(int i=0;i<num;i++){
														cout<<"\t\t "<<row[i];
													}
													cout << endl;
												}
												mysql_free_result(res);
											}
										}
										getch();
									break;
								}
								case 0:
								{
									quit3=true;
									break;
								}
								default :{
										system("cls");
										cout<<"invalid choice"<<endl;
										break;
								}
							}
						}while(!quit3);
							
							}else{
								cout<<endl;
								cout<<"admin nom ou mot de passe invalide";
								getch();								
							}
						}
				}
				break;
			}		
			case 0 : {
				quit=true;
				break;
			}
			default:{
				system("cls");
				cout<<"invalid choice"<<endl;
				break;
			}
										
					
					
		}
	}while(!quit);
	
	
	return 0;
}
