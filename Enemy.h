#pragma once
#include "Raptor.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Enemy{
private:
	// enemy name, health, currenthealth, maxhealth, damage, luck, and an array of their loot
	string ename;
	int espeed;
	int ecurrhealth;
	int emaxhealth;
	int edamage;
	int eluck;
	string eloot[10];

public:
	Enemy();
	void setStats(string, int, int, int, int);
	bool knownItems(string, string);
	// Starts a fight with the Raptor using a turn based fight.
	void fightSequence(Raptor &raptor);
	//Checks if current health is zero, and ends the fight if either are.
	bool EnemyisDead();
	void dealDamage(int);
	bool RaptorisDead(Raptor &raptor);
	//A method that adds items to the Raptors inventory, or gives a choice to switch if the inventory is already full.
	void addloot(string);
	int getluck();
	void loadLoot(string);
	void giveloot(Raptor &raptor);
	void looteffect(Raptor &raptor);








};