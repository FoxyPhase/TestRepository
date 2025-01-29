#ifndef DATABASE_H
#define DATABASE_H

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <windows.h>
#include <iostream>
#include <memory>  // Для unique_ptr

using std::endl;
using std::cout;

void static setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class DataBase {
private:
    std::unique_ptr<sql::Connection> conn;
public:
    DataBase();  // Конструктор
    ~DataBase(); // Деструктор

    sql::Connection* getConnection();
};

#endif
