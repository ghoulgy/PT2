#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "addon.h"
using namespace std;

bool AddOn::got_food = false;
bool AddOn::got_drink = false;

//Show the add on menu
void AddOn::display_addOn(){
	char main;
	int choice;
	long add_on;
	cout << "Add-on menu" << endl;

	fstream food_menu("addOn_food.dat", ios::in|ios::binary);
	fstream drink_menu("addOn_drink.dat", ios::in|ios::binary);
	
	if(!food_menu.fail() && !drink_menu.fail()){
		do{
			cout << "1. Foods" << endl;
			cout << "2. Drinks" << endl;
			cout << "Choose which one: ";
			cin >> choice;
			system("cls");
			switch(choice){
				case 1:
					food_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));

					cout << "==================== XYZ Food Menu ====================" << endl;
					cout << left << setw(15)<<"No." << setw(25) << "Name" << setw(15) << "Price(RM)" << endl;
					cout << "-------------------------------------------------------" << endl;
					cout << fixed << setprecision(2);
					while(!food_menu.eof()){
						cout << left << setw(15) << addon.food_i << setw(25) << addon.food_name << setw(15) << addon.food_price << endl;
						food_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));
					}
					cout << "==================== XYZ Food Menu ====================" << endl << endl;

					food_menu.close();
					
					cout << "Buy which items: ";
					cin >> add_on;
					buy_addOn_food(add_on);
					break;
					
				case 2:
					drink_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));
					
					cout << "==================== XYZ Drink Menu ====================" << endl;
					cout << left << setw(15)<<"No." << setw(25) << "Name" << setw(15) << "Price(RM)" << endl;
					cout << "-------------------------------------------------------" << endl;
					while(!drink_menu.eof()){
						cout << left << setw(15) << addon.drink_i << setw(25) << addon.drink_name << setw(15) << addon.drink_price << endl;
						drink_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));
					}
					cout << "==================== XYZ Drink Menu ====================" << endl << endl;

					drink_menu.close();
					
					cout << "Buy which items: ";
					cin >> add_on;
					buy_addOn_drink(add_on);
					break;
			}
			cout << "Return menu? (Y/N): ";
			cin >> main;
			cin.ignore();
		}while(toupper(main)=='Y');
	}else{
		cout << "Read file error!" << endl;
	}

}

//Buy add on food
void AddOn::buy_addOn_food(long i){
			
	char confirm;
	int bil;
	fstream food_menu("addOn_food.dat", ios::in|ios::binary);
	
	if(!food_menu.fail()){
		food_menu.seekg((i-1) * sizeof(addon), ios::beg);
		food_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));
		cout << "\nPrice of food(one): RM" << addon.food_price << endl; 
		cout << "Buy how much: ";
		cin >> bil;
		tot_price_food = bil * addon.food_price; 
		cout << "Total price is: RM" << tot_price_food << endl;
		cout << "\nComfirm to buy?(Y/N): ";			
		cin >> confirm;								//Comfirmation to buy food
		if(toupper(confirm)=='Y'){
			cout << "\nPurchased successfully" << endl;
			got_food = true; 						// Food purchased
		}else{
			cout << "Skip" << endl;
		}
		system("pause");
		system("cls");
	}else{
		cout << "Error open file." << endl;
	}
	
	food_menu.close();
}

//Buy add on drink
void AddOn::buy_addOn_drink(long i){
			
	char confirm;
	int bil;
	fstream drink_menu("addOn_drink.dat", ios::in|ios::binary);
	
	if(!drink_menu.fail()){
		drink_menu.seekg((i-1) * sizeof(addon), ios::beg);
		drink_menu.read(reinterpret_cast<char *>(&addon), sizeof(addon));
		cout << "\nPrice of drink(one): RM" << addon.drink_price << endl; 
		cout << "Buy how much: ";
		cin >> bil;
		tot_price_drink = bil * addon.drink_price; 
		cout << "Total price is: RM" << tot_price_drink << endl;
		cout << "\nComfirm to buy?(Y/N): ";
		cin >> confirm;								//Comfirmation to buy food
		if(toupper(confirm)=='Y'){
			cout << "Purchased successfully" << endl;
			got_drink = true; 						//Drinks purchased
		}else{
			cout << "Skip" << endl;
		}
		system("pause");
		system("cls");
	}else{
		cout << "Error open file." << endl;
	}
	
	drink_menu.close();
}
