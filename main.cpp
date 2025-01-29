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



void addPlayer(sql::Connection* conn, const std::string& name, int health) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO players (name, health) VALUES (?,?)"));
        pstmt->setString(1, name);
        pstmt->setInt(2, health);
        pstmt->executeUpdate();
        setConsoleColor(2);
        cout << "Игрок добавлен!" << endl;
        setConsoleColor(7);
    }
    catch (sql::SQLException e) {
        setConsoleColor(4);
        std::cerr << "Ошибка добавления: " << e.what() << endl;
        setConsoleColor(7);
    }
};

void deletePlayer(sql::Connection* conn, const std::string& name) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("DELETE FROM players WHERE name = ?"));
        pstmt->setString(1, name);
        int rowsAffected = pstmt->executeUpdate();

        if (rowsAffected > 0) {
            setConsoleColor(2);
            cout << "Игрок успешно удалён!" << endl;
            setConsoleColor(7);
        }
        else {
            setConsoleColor(6);
            cout << "Игрок не найден." << endl;
            setConsoleColor(7);
        }
    }
    catch (sql::SQLException e) {
        setConsoleColor(4);
        cout << "Ошибка удаления: " << e.what() << endl;
        setConsoleColor(7);
    }
}

int main() {
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    DataBase db;

    sql::Connection* conn = db.getConnection();

    
    
   

    return 0;
}