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
	int id;
	inventory playerInventory;
public:
	player(sql::Connection* conn, const std::string& n, const std::string& pass, const std::string& signType);
	~player();
	
	

	void getDamage(sql::Connection* conn, int quanity);
	void healPlayer(sql::Connection* conn, int quanity);

	void loadPlayerInventory(sql::Connection* conn);
	void addPlayerInventory(sql::Connection* conn, const std::string& itemName);
	void delPlayerInventory(sql::Connection* conn, const std::string& itemName);
};

#endif