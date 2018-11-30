/*What this file includes
	Collision Class
	Enemy Class

	Important Notes:
		All uses of this class are being put instantly
		into the main cpp file. None are in Anthony.cpp
*/
#ifndef anthonyR_H
#define anthonyR_H

#include <iostream>

class Collision {
public:
	bool contact;
	bool punching;
	bool range;
	bool restrict;

	enum moveSet {
		Punch = 0	
	};

	Collision() {
		contact = false;	
		punching = false;
		range = 1000;
		restrict = false;
	}
	bool Within_Range(int range) {
		if (range > 400 && range < 600) {
			this->range = range;
			return true;
		}
		return false;
	}
	bool Punching(bool flag) {
		punching = flag;
		return flag;
	}
	int Damage() {
		if (restrict == true)	
			return 20;
		if (punching == true)
			return 0;
		return 20;		
	}
	void Check_For_Hit() {
		if (punching) {
			contact = true;
			//Damage();
		}		
	}
};

class Enemy {
public:
	int health;
	Enemy() { health = 100; }
};
#endif

