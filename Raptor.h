#pragma once
#include <iostream>

using namespace std;
class Raptor {
protected:
	//Raptor name, maxhealth, currenthealth, speed, damage, money and luck.
	string name;
	int maxhealth;
	int currhealth;
	int speed;
	int damage;
	int money;
	int luck;
	// Stores the current items that are known, what they do, how big of a change it is, and a description of the item.
	string loot[10];
	string knownitems[20];
	string itemeffect[20];
	int itemmagnitude[20];
	string itemdescription[20];
	



public:
	Raptor();
	//Sets the stats of the new Raptor
	void setStats(string, int, int, int, int);
	//Getters
	string getName(void);
	int getmaxhealth(void);
	int getcurrhealth(void);
	int getspeed(void);
	int getdamage(void);
	int getluck(void);
	void addspeed(int);
	void adddamage(int);
	void addluck(int);
	void addmaxhealth(int);
	void losehealth(int);
	//Prints what the raptor looks like in ASCII art
	int portrait(string);
	//Prints a display that shows the current stats of the particular raptor
	void getStats(void);
	//Adds an item to the raptors inventory
	void addInv(string);
	//Uses an item that will do various things for the raptor
	void UseItem(string);
	void GameOver();
	void gainhealth(int);
	void loaditems(string);
	bool intimidateCheck(int);
	int randint(int);
	void addloot(string);









};