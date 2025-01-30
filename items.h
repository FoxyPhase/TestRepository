#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>

class item {
public:
    item();
    ~item();

    void static showAllItems(sql::Connection* conn);

private:
    std::string name, description;
    int canUse;
};

#endif