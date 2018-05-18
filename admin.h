#ifndef ADMIN_H
#define ADMIN_H

//Admin class
class Admin : public Buy{
	private:
		string name, password;
		bool correct;
	public:
		void setName(string u_name){
			name = u_name;
		};
		void setPass(string u_password){
			password = u_password;
		};
		string getName(){return name;};
		string getPass(){return password;};
		void see_psgnr();
		void addOn_input();
		void edit_table();
		void add_table();
		bool isCorrect();
};

#endif
