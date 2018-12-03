/*What this file includes
	Collision Class
	Enemy Class

*/
#ifndef anthonyR_H
#define anthonyR_H
#include "emmanuelC.h"

class Peter {
public:
	int health;
	int x;
	int y;
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxLEFT;
	int yHitBoxRIGHT;
	Peter() {
		x = 0;	
		y = 0;
		xHitBoxLEFT = 0;
		xHitBoxRIGHT = 0;
		yHitBoxLEFT = 0;
		yHitBoxRIGHT = 0;
		health = 80;
	}
};

class Collision {
public:
	bool contact;
	bool punching;
	bool range;
	bool restrict;
	int collisionX;
	int collisionY;
	int peterY;
	enum moveSet {
		Punch = 0	
	};

	Collision() {
		contact = false;	
		punching = false;
		range = 1000;
		restrict = false;
		peterY = 0;
		collisionX = 0;
		collisionY = 0;
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

class Spike {
public:
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxLEFT;
	int yHitBoxRIGHT;
	Spike()
	{
		xHitBoxLEFT = 0; //Fixed Locations for every Spike
		xHitBoxRIGHT = 0;
		yHitBoxLEFT = 0;
		yHitBoxRIGHT = 0;
	}
	bool Spike_Collision();
};
#endif












