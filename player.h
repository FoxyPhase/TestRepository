#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "inventory.h"	
#include "colors.h"

class player{
private:
	std::string name, password;
	int health;
	int chapter;
	inventory playerInventory;
	int id;
public:
	player(sql::Connection* conn, const std::string& n, const std::string& pass, const std::string& signType);
	~player();

	void getDamage(sql::Connection* conn, int quanity);
	void healPlayer(sql::Connection* conn, int quanity);


};

#endif