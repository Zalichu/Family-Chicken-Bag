/*What this file includes
	Collision Class
	Enemy Class

*/
#ifndef anthonyR_H
#define anthonyR_H
#include "emmanuelC.h"

extern Global gl;

class Peter {
public:
	int health;
	int x;
	int y;
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxBOTTOM;
	int yHitBoxTOP;
	Peter() {
		x = 0;	
		y = 0;
		xHitBoxLEFT = 0;
		xHitBoxRIGHT = 0;
		yHitBoxBOTTOM = 0;
		yHitBoxTOP = 0;
		health = 100;
	}
	void getPeterPos();
	bool Alive();
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
	int x;
	int y;
	bool showImage;
	Enemy() 
	{
		x = 0;
		y = 0; 
		health = 100; 
		showImage = true;
	}
};

class Spike {
public:
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxBOTTOM;
	int yHitBoxTOP;
	Spike()
	{
		xHitBoxLEFT = 290; //Fixed Locations for every Spike
		xHitBoxRIGHT = 520;
		yHitBoxBOTTOM = 0;
		yHitBoxTOP = 0;
	}
	bool Spike_Collision();
	void Within_Range(int x, int y, Peter &peter);
};

class Death {
public:
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxBOTTOM;
	int yHitBoxTOP;
	Death()
	{
		xHitBoxLEFT = 290; //Fixed Locations for every Spike
		xHitBoxRIGHT = 520;
		yHitBoxBOTTOM = 0;
		yHitBoxTOP = 0;
	}
};

class NinjaStar {
public:
	int xHitBoxLEFT;
	int xHitBoxRIGHT;
	int yHitBoxBOTTOM;
	int yHitBoxTOP;
	int damage;
	NinjaStar() 
	{	
		xHitBoxLEFT = 0; //Hit boxes will be changing 
		xHitBoxRIGHT = 0;
		yHitBoxBOTTOM = 0;
		yHitBoxTOP = 0;
		damage = 100;
	}
};
#endif
















