#include "database.h"
#include <iostream>

// �����������
DataBase::DataBase() {
    try {
        sql::Driver* driver = get_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306?useUnicode=true&characterEncoding=UTF-8", "root", "Bad06102006"));
        conn->setSchema("my_game_database");
        setConsoleColor(2);
        std::cout << "����������� �����������!" << std::endl;
        setConsoleColor(7);
    }
    catch (sql::SQLException& e) {
        setConsoleColor(4);
        std::cerr << "������ �����������: " << e.what() << endl;
        exit(1);
        setConsoleColor(7);
    }
}

// ����������
DataBase::~DataBase() {
    setConsoleColor(2);
    std::cout << "���������� �������!" << std::endl;
    setConsoleColor(7);
}

// ����� ��� ��������� �����������
sql::Connection* DataBase::getConnection() {
    return conn.get();
}
