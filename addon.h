#ifndef ADDON_H
#define ADDON_H

//Add-on menu
class AddOn : public Timetable{
	protected:
		static bool got_food;
		static bool got_drink;
		float tot_price_food, tot_price_drink;
		struct addOn{
			int food_i, drink_i;
			float food_price, drink_price;
			char food_name[50], drink_name[50];
		} addon;
	public:
		void display_addOn();
		void buy_addOn_food(long);
		void buy_addOn_drink(long);
};

#endif
