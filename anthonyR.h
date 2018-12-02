/*What this file includes
	Collision Class
	Enemy Class

	Important Notes:
		All uses of this class are being put instantly
		into the main cpp file. None are in Anthony.cpp
*/
#ifndef anthonyR_H
#define anthonyR_H
#include "emmanuelC.h"

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
	bool Within_Range(int range); 
	bool Punching(bool flag);
	int Damage(); 
	void Check_For_Hit(); 
};

class Enemy {
public:
	int health;
	Enemy() { health = 100; }
};

#endif

