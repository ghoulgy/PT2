#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "admin.h"
using namespace std;


//Check admin password is correct or not
bool Admin::isCorrect(){
	bool correct = false;
	string text, user_ad, pass_ad;
	fstream info_ad("admin.txt", ios::in);
	
	if(!info_ad.fail()){
		while(!info_ad.eof()){
			getline(info_ad, user_ad, ';');
			getline(info_ad, pass_ad, ' ');
			
			if(user_ad.compare(name)==0 && pass_ad.compare(password)==0 && !correct){
					cout << "You are enter as admin!" << endl;
					correct = true;
				} else{
					cout << "Wrong user and password" << endl;
					correct = false;
				}
			}
	}else{
		cout << "File not found" << endl;
		correct = false; 	
	}
	
	info_ad.close();
	return correct;
}

//Add on menu input
void Admin::addOn_input(){
	char again;
	int choice;
	
	cout << "Edit add on menu:" << endl;

	fstream food_menu("addOn_food.dat", ios::out|ios::binary|ios::app);
	fstream show_food("addOn_food.dat", ios::in);
	fstream drink_menu("addOn_drink.dat", ios::out|ios::binary|ios::app);
	fstream show_drink("addOn_drink.dat", ios::in);

	
	cout << "Enter Your add-on menu: " << endl;
	cout << "1. Foods" << endl;
	cout << "2. Drinks" << endl;
	cout << "3. Cancel" << endl;
	cout << "Your choice: " ;
	cin >> choice;
	system("cls");
	
	switch(choice){
		case 1:
			if(food_menu.fail()){
				cout << "Error when open food menu!" << endl;
				exit(0);
			}
			
			if(!show_food.fail()){			
				show_food.read(reinterpret_cast<char *>(&addon), sizeof(addon));
				cout << "==================== Current Food Menu ====================" << endl;
				cout << left << setw(15)<<"No." << setw(25) << "Name" << setw(15) << "Price(RM)" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cout << fixed << setprecision(2);
				while(!show_food.eof()){
					cout << left << setw(15) << addon.food_i << setw(25) << addon.food_name << setw(15) << addon.food_price << endl;
					show_food.read(reinterpret_cast<char *>(&addon), sizeof(addon));			
				}
				cout << "==================== Current Food Menu ====================" << endl << endl;
				show_food.close();
			}
			
			cout << "Enter food menu:" << endl;
			do{
				cout << "No: ";
				cin >> addon.food_i;
				cin.ignore();
				cout << "Food Name: ";
				cin.getline(addon.food_name, 50);
				cout << "Food Price(one): ";
				cin >> addon.food_price;

				food_menu.write(reinterpret_cast<char *>(&addon), sizeof(addon));

				cout << "\nAgain? or press n to exit: ";
				cin >> again;
				
			}while(toupper(again)!='N');
			cout << "Edited successfully!" << endl;
			break;
		case 2:
			if(drink_menu.fail()){
				cout << "Error when open food menu!" << endl;
				exit(0);	
			}
			
			show_drink.read(reinterpret_cast<char *>(&addon), sizeof(addon));
			if(!show_drink.fail()){
				cout << "==================== Current Food Menu ====================" << endl;
				cout << left << setw(15)<<"No." << setw(25) << "Name" << setw(15) << "Price(RM)" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cout << fixed << setprecision(2);
				while(!show_drink.eof()){
					cout << left << setw(15) << addon.drink_i << setw(25) << addon.drink_name << setw(15) << addon.drink_price << endl;
					show_drink.read(reinterpret_cast<char *>(&addon), sizeof(addon));
				}
				cout << "==================== Current Food Menu ====================" << endl << endl;
				show_drink.close();
			}
			
			cout << "Enter drink menu:" << endl;
			do{
				cout << "No: ";
				cin >> addon.drink_i;
				cin.ignore();
				cout << "Drink Name: ";
				cin.getline(addon.drink_name, 50);
				cout << "Drink Price(one): ";
				cin >> addon.drink_price;
				
				drink_menu.write(reinterpret_cast<char *>(&addon), sizeof(addon));

				cout << "\nAgain? or press n to exit: ";
				cin >> again;
			}while(toupper(again)!='N');
			cout << "Edited successfully!" << endl;
			break;
		case 3:
			break;
	}
	food_menu.close();
	drink_menu.close();

}

//Edit the schedule
void Admin::edit_table(){
	long edit;

	cout << "\nEdit schedule: " << endl;
	
	fstream file("a.dat", ios::in | ios::out | ios::binary);
	
	cout << "\nType the no that you want to edit : ";
	cin >> edit;
	cin.ignore();
	
	file.seekg((edit-1) * sizeof(table),ios::beg);
	file.read(reinterpret_cast<char *>(&table), sizeof(table));
	
	//Showing the chosen data that want to edit
	cout << left << setw(5) << "No" << setw(15) << "Departure" << setw(13) << "Arrival";
	cout << setw(13) << "Time Depart" << setw(14) << "Time Arrival" << setw(10) << "ETA" << setw(10) << "Seats Left";
	cout << left << setw(5) << table.no << setw(15) << table.depart << setw(13) << table.arrive << setw(13) << table.time_d;
	cout << setw(14) << table.time_a << setw(10) << table.ETA << setw(10) << table.seatLeft;
	
	//Enter a new data to replace the old data
	cout << "\nEnter new record data: " << endl;
	
	cout << "Enter departure: ";
	cin.getline(table.depart, 800);
	
	cout << "Enter arrival: ";
	cin.getline(table.arrive, 800);
	
	cout << "Enter time depart: ";
	cin >> table.time_d;
	
	cout << "Enter time arrival: ";
	cin >> table.time_a;
	
	cout << "Enter ETA : ";
	cin >> table.ETA;
	
	cout << "Enter seat left: ";
	cin >> table.seatLeft;
	cin.ignore();

	file.seekp((edit-1) * sizeof(table), ios::beg);
	file.write(reinterpret_cast<char *>(&table), sizeof(table));
	
	file.close();
}

//Add schedule
void Admin::add_table(){
	
	char again;
	fstream open("a.dat", ios::out|ios::binary|ios::app);
	
	cout << "\nAdd a new journey: " << endl;
	
	do{
		cout << "Enter ticket no: ";
		cin.getline(table.no, 800);
		
		cout << "Enter departure: ";
		cin.getline(table.depart, 800);
		
		cout << "Enter arrival: ";
		cin.getline(table.arrive, 800);
		
		cout << "Enter time depart: ";
		cin >> table.time_d;
		
		cout << "Enter time arrival: ";
		cin >> table.time_a;
		
		cout << "Enter ETA : ";
		cin >> table.ETA;
		
		cout << "Seat Left: ";
		cin >> table.seatLeft;
		cin.ignore();
	
		open.write(reinterpret_cast<char *>(&table), sizeof(table));

		cout << "Again? or press 'n' to exit. ";
		cin >> again;
		cin.ignore();
		
	}while(toupper(again)!='N');
	
	open.close();

	cout << "\nUpdate completed!" << endl;
}

//See passenger details
void Admin::see_psgnr(){
	int i=0;
	string user[50], pass[50];
	
	cout << "All passengers detail: " << endl;

	fstream info("user.txt", ios::in);
	
	if(!info.fail()){
		while(!info.eof()){
			getline(info,user[i],';');
			getline(info,pass[i],' ');
			
			//To avoid printing empty value
			if(info.eof()){
				break;
			}
			
			cout << "No: " << i+1 << endl;
			cout << "Name: " << user[i] << endl;
			cout << "Password: " << pass[i] << endl << endl;
			i++;
		}
	}else{
		cout << "Error Read User File..." << endl;
	}
	info.close();
}

