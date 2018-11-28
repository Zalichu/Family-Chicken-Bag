#ifndef anthonyR_H
#define anthonyR_H

#include <iostream>

class Collision {
public:
	bool contact;
	bool punching;
	bool range;

	enum moveSet {
		Punch = 0	
	};

	Collision() {
		contact = false;	
		punching = false;
		range = 1000;
	}
	bool Within_Range(int range) {
		if (range > 600 && range < 700) {
			this->range = range;
			std::cout << " IN RANGE";
			return true;
		}
		return false;
	}
	bool Punching(bool flag) {
		punching = flag;
		return flag;
	}
	int Damage() {
		if (punching == true)
			return 20;
		return 0;		
	}
	void Check_For_Hit() {
		if (punching) {
			contact = true;
			//Damage();
		}		
	}
};

#endif

