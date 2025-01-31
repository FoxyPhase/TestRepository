#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "colors.h"

class player; 

struct item {
	std::string name, description;
	int canUse;
};

class inventory {
private:
	std::vector<item> Items;
public:
	inventory();
	~inventory();

	void addItem(sql::Connection* conn, int plr_id, const std::string& name);
	void delItem(sql::Connection* conn, int plr_id, const std::string& name);
	void useItem();

	void loadInventory(sql::Connection* conn, int player_id);

};

#endif
