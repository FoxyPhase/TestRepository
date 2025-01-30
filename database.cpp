#include "database.h"
#include "colors.h"
#include <iostream>

DataBase::DataBase() {
    try {
        sql::Driver* driver = get_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306?useUnicode=true&characterEncoding=UTF-8", "root", "Bad06102006"));
        conn->setSchema("my_game_database");
        greenColor();
        std::cout << "Подключение установлено!" << std::endl;
        standartColor();
    }
    catch (sql::SQLException& e) {
        redColor();
        std::cerr << "Ошибка подключения: " << e.what() << endl;
        exit(1);
        standartColor();
    }
}

DataBase::~DataBase() {
    greenColor();
    std::cout << "Соединение закрыто!" << std::endl;
    standartColor();
}

sql::Connection* DataBase::getConnection() {
    return conn.get();
}
