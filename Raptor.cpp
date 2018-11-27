#include <iostream>
#include <string>
#include <fstream>
#include "Raptor.h"
#include <sstream>
#include <time.h> 
#include <chrono>
#include "Enemy.h"
#include <conio.h>

using namespace std;


Raptor::Raptor() {
	name = "";
	maxhealth = 0;
	currhealth = maxhealth;
	speed = 0;
	damage = 0;
	luck = 0;
	for (int i = 0; i < 10; i++)
		loot[i] = "";
}
//Getters and setters, as well as the ability to add stats
int Raptor::getmaxhealth(void) {
	return maxhealth;
}

int Raptor::getcurrhealth(void) {
	return currhealth;
}

int Raptor::getspeed(void) {
	return speed;
}

int Raptor::getdamage(void) {
	return damage;
}

void Raptor::adddamage(int plus) {
	damage = damage + plus;
}

void Raptor::addspeed(int plus) {
	speed = speed + plus;
}

void Raptor::addmaxhealth(int plus) {
	maxhealth = maxhealth + plus;
	currhealth = currhealth + plus;
}

// This function should be called whenever creating a new raptor.
void Raptor::setStats(string rname, int rhealth, int rspeed, int rdamage, int nluck) {
	name = rname;
	maxhealth = rhealth;
	speed = rspeed;
	damage = rdamage;
	currhealth = maxhealth;
	luck = nluck;
	for (int i = 0; i < 10; i++) {
		loot[i] = "";
	}

}
// Two getters
string Raptor::getName(void) {
	return name;
}

int Raptor::getluck(void) {
	return luck;
}
// A picture of the Raptor, read in from a file
int Raptor::portrait(string filename) {
	ifstream reader(filename, ios::in);
	if (reader.fail()) {
		return -1;
	}
	string line;
	while (!reader.eof()) {
		getline(reader, line);
		cout << line << endl;
	}
	reader.close();
	return 0;

}

//A HUB for the user to easily view their Raptors stats
void Raptor::getStats(void) {
	string pause;
	portrait("Raptorface.txt");
	cout << "-----------------------------------------" << endl;
	cout << "Name: " << name << endl; 
	cout << "Health: " << currhealth << "/" << maxhealth << endl;
	cout << "Speed: " << speed << endl;
	cout << "Luck: " << luck << endl;
	cout << "Damage: " << damage << endl;
	cout << "Current inventory: ";
		for (int i = 0; i < 10; i++) {
			if (loot[i] != "") {
				cout << loot[i] << " ";
			}
	}
	cout << endl;
	cout << "-----------------------------------------" << endl;
	int c;
	printf("Press any key to continue...");
	cout << endl;
	c = _getch();
	if (c == 0 || c == 224)
		_getch();

}
//Two functions that allow the user to take away health and heal the raptor.
void Raptor::losehealth(int amount) {
	currhealth = currhealth - amount;
	if (currhealth <= 0) {
		GameOver();
	}
}

void Raptor::gainhealth(int amount) {
	cout << name << " has been healed " << amount << " health! " << endl;
	if (amount + currhealth > maxhealth)
	{
		currhealth = maxhealth;
	}
	else
		currhealth = currhealth + amount;
}
//Intentional "infinite" loop prompting the user to exit the program. GAME OVER.
void Raptor::GameOver() {
	int sad = 0;
	portrait("Game_Over.txt");
	while (sad != 8675309) {
		cin >> sad;
	}
}
// Loads the game's known items into three arrays.
void Raptor::loaditems(string filename){
	ifstream file(filename, ios::in);
	if (file.fail())
		cout << "Failed to read file!" << endl;
	string line;
	int counter = 0;
	while (!file.eof()) {
		getline(file, line, ' ');
		knownitems[counter] = line;
		getline(file, line, ' ');
		istringstream ss1(line);
		ss1 >> itemeffect[counter];
		getline(file, line, ' ');
		istringstream ss(line);
		ss >> itemmagnitude[counter];
		getline(file, line);
		counter++;
	}
	file.close();





}

void Raptor::addInv(string item) {


}

//Checks to see whether the Raptor's random roll overcomes the luck passed into the function using randint()
bool Raptor::intimidateCheck(int eluck) {
	int enemychance = eluck;
	int raptorchance = getluck();
	for (int i = 0; i < 20; i++) {
		if (randint(enemychance) > randint(raptorchance))
			return false;
		if (randint(enemychance) < randint(raptorchance))
			return true;
	}



}

//Returns a random number that is lower than the maximum. (which is 100)
int Raptor::randint(int max) {

	srand(time(NULL));
	int randnum = 150;
	while (randnum > max) {
		randnum = rand();
	}
	return randnum;
}

//Adds an item to the Raptor's inventory. It then checks to see the item effect, and changes the Raptors stats accordingly.
void Raptor::addloot(string nloot) {
	for (int i = 0; i < 10; i++) {
		if (loot[i] == ""){
			loot[i] = nloot;
			break;
		}
	}
	for (int i = 0; i < 20; i++) {
		if (nloot == knownitems[i]){
			string type = itemeffect[i];
			int bonus = itemmagnitude[i];
			if (type == "speed") {
				speed = speed + bonus;
				if (speed < 0)
					speed = 0;
				break;
			}
			else if (type == "damage") {
				damage = damage + bonus;
				if (damage < 0)
					damage = 0;
				break;
			}
			else if (type == "maxhealth") {
				maxhealth = maxhealth + bonus;
				currhealth = currhealth + bonus;
				break;
			}
			else if (type == "luck") {
				luck = luck + bonus;
				if (luck < 0)
					luck = 0;
				break;
			}
		}
	}
	
}





