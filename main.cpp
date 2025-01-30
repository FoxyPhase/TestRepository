#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <chrono>
#include <thread>
#include <limits>
#include <windows.h>
#include <sstream>
#include <set>
#include <unordered_set>
#include <forward_list>
#include <cctype>
#include <ctime>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "database.h"
#include "colors.h"
#include "inventory.h"

using std::cout;
using std::endl;
using std::cin;

void static ClearInputBuffer(char delimiter = '\n') {
    cin.clear();
    cin.ignore(1000, delimiter);
}

void static clear() {
    system("cls");
}

void static wait(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
}


void static addPlayer(sql::Connection* conn, const std::string& name, int health) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO players (name, health) VALUES (?,?)"));
        pstmt->setString(1, name);
        pstmt->setInt(2, health);
        pstmt->executeUpdate();
        greenColor();
        cout << "Игрок добавлен!" << endl;
        standartColor();
    }
    catch (sql::SQLException e) {
        redColor();
        std::cerr << "Ошибка добавления: " << e.what() << endl;
        standartColor();
    }
};

void static deletePlayer(sql::Connection* conn, const std::string& name) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("DELETE FROM players WHERE name = ?"));
        pstmt->setString(1, name);
        int rowsAffected = pstmt->executeUpdate();

        if (rowsAffected > 0) {
            greenColor();
            cout << "Игрок успешно удалён!" << endl;
            standartColor();
        }
        else {
            yellowColor();
            cout << "Игрок не найден." << endl;
            standartColor();
        }
    }
    catch (sql::SQLException e) {
        redColor();
        cout << "Ошибка удаления: " << e.what() << endl;
        standartColor();
    }
}

void static showPlayers(sql::Connection* conn) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM players"));
        std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());

        while (result->next()) {
            cout << "ID: " << result->getInt("id") << ", ";
            cout << "Name: " << result->getString("name") << ", ";
            cout << "Health: " << result->getInt("health") << "." << endl;
        }

    }
    catch (sql::SQLException e) {
        redColor();
        std::cerr << "Ошибка: " << e.what() << endl;
        standartColor();
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    DataBase db;

    sql::Connection* conn = db.getConnection();

    inventory s;
    s.addItem(conn, "Knife");
    s.delItem();
    
    return 0;
}