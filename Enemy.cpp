#pragma once
#include <iostream>
#include "Enemy.h"
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;
//Constructor
Enemy::Enemy() {
	ename = "NULL";
	espeed = 0;
	emaxhealth = 1;
	ecurrhealth = 1;
	edamage = 0;
}
//Sets the Enemy's base statistics
void Enemy::setStats(string nname, int nmaxhealth, int ndamage, int nspeed, int nluck){
	ename = nname;
	espeed = nspeed;
	emaxhealth = nmaxhealth;
	ecurrhealth = nmaxhealth;
	edamage = ndamage;
	eluck = nluck;
	for (int i = 0; i < 10; i++) {
		eloot[i] = "";
	}
}
// Checks to see if an item is located within a file.
bool Enemy::knownItems(string item, string filename) {
	ifstream file(filename, ios::in);
		if (file.fail())
			return false;
	string line;
	while (!file.eof()) {
		getline(file, line, ' ');
		if (item == line) {
			return true;
		}
		getline(file, line);
	}
	return false;

}

//Checks to see if the Enemy's health hits zero
bool Enemy::EnemyisDead(){
	if (ecurrhealth == 0 || ecurrhealth < 0)
		return true;
	else
		return false;

}
//Checks to see if the raptor's health has hit zero.
bool Enemy::RaptorisDead(Raptor &raptor) {
	int raptorshealth = raptor.getcurrhealth();
	if (raptorshealth == 0 || raptorshealth < 0)
		return true;
	else
		return false;
}
//Adds a peice of loot to the Enemy's inventory
void Enemy::addloot(string nloot) {
	for (int i = 0; i < 10; i++) {
		if (eloot[i] == "") {
			eloot[i] = nloot;
			break;
		}
	}

}
//Allows damage to be subtracted from the enemy's current health.
void Enemy::dealDamage(int damage) {
	ecurrhealth = ecurrhealth - damage;
}
/*A function that simulates a fight. It has multiple outcomes.
1) The raptor is depleted to 0 health and the user gets game over
2) The enemy is depleted to 0 health and the user continues the story
3) The enemy is intimidated based on a luck check, and the user continues
4) The user successfully runs away
*/
void Enemy::fightSequence(Raptor &raptor) {
	char choice;
	int rdamage = 0;
	while (!RaptorisDead(raptor) && !EnemyisDead()) {
		cout << "(1) Attack" << endl;
		cout << "(2) Intimidate" << endl;
		cout << "(3) Run" << endl;
		cin >> choice;
		while (choice != '1' && choice != '2' && choice != '3') {
			cout << "Not a valid choice, please try again!" << endl;
			cin >> choice;
		}
		if (choice == '1') {
			rdamage = raptor.getdamage();
			cout << "Your raptor slashes out, dealing " << rdamage << " damage!" << endl;
			dealDamage(rdamage);
			if (EnemyisDead()) {
				//Add code to give loot to the user
				cout << "With a mightly slash, " << ename << " falls to the floor, dead and defeated" << endl;
				break;
			}
		}
		else if (choice == '2') {
			int echeck = getluck();
			bool isintimidated = raptor.intimidateCheck(echeck);
			if (isintimidated) {
				cout << ename << " runs in fear at your mightly roar!" << endl;
					break;
			}
			else {
				cout << ename << " is unphased at your attempts!" << endl;
			}
		}
		else if (choice == '3') {
			cout << "You attempt to run away!" << endl;
			if (raptor.getspeed() > espeed) {
				cout << "You successfully run away!" << endl;
			}
			else {
				cout << "You try to run away, but are unsuccessful!" << endl;
			}
		}
		cout << ename << " swipes back, dealing " << edamage << " damage!" << endl;
		raptor.losehealth(edamage);
	}
	if (RaptorisDead(raptor))
		raptor.GameOver();
	

}
// Getter for luck
int Enemy::getluck() {
	return eluck;
}
// Gives the raptor all the loot from the enemy's inventory
void Enemy::giveloot(Raptor &raptor){
	loadLoot("EnemyLoot.txt");
	for (int i = 0; i < 10; i++){
		if (eloot[i] != "") {
			raptor.addloot(eloot[i]);
		}
	}
}

// Loads common loot for enemy's from a .txt file. For example, the enemy Drunkman loads a PokingStick.
void Enemy::loadLoot(string filename) {
	ifstream File(filename, ios::in);
	if (File.fail())
		cout << "Enemy LoadLoot failed to load!" << endl;
	string line;
	int counter = 0;
	while (!File.eof()) {
		getline(File, line, ' ');
		if (line == ename) {
			getline(File, line);
			eloot[counter] = line;
			break;
		}
		else {
			getline(File, line);
		}
	}
	File.close();


}








