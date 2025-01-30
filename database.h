#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <windows.h>
#include <iostream>
#include <memory>

using std::endl;
using std::cout;

class DataBase {
private:
    std::unique_ptr<sql::Connection> conn;
public:
    DataBase();  
    ~DataBase(); 

    sql::Connection* getConnection();
};

#endif
