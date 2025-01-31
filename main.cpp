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
#include "player.h"

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

void sign(sql::Connection* conn, std::unique_ptr<player>& plr);
void checkLogin(sql::Connection* conn, std::unique_ptr<player>& plr);
void checkRegister(sql::Connection* conn, std::unique_ptr<player>& plr);

int main() {
    setlocale(LC_ALL, "Ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    DataBase db;

    sql::Connection* conn = db.getConnection();

    std::unique_ptr<player> currentPlayer = nullptr;

    sign(conn, currentPlayer);


    currentPlayer->loadPlayerInventory(conn);
    currentPlayer->delPlayerInventory(conn, "Knife");
    currentPlayer->loadPlayerInventory(conn);


    return 0;
}

void sign(sql::Connection* conn, std::unique_ptr<player>& plr) {
    try {
        bool accountHave = false;
        while (accountHave == false) {
            int userInput;
            cout << "У вас есть аккаунт?" << endl;
            cout << "1. Да\n2.Нет" << endl;
            cin >> userInput;
            if (!cin.fail()) {
                switch (userInput)
                {
                case 1:
                    checkLogin(conn, plr);
                    greenColor();
                    cout << "Добро пожаловать!" << endl;
                    standartColor();
                    accountHave = true;
                    break;
                case 2:
                    checkRegister(conn, plr);
                    greenColor();
                    cout << "Добро пожаловать!" << endl;
                    standartColor();
                    accountHave = true;
                    break;
                default:
                    yellowColor();
                    cout << "Выберите первое или второе!" << endl;
                    ClearInputBuffer();
                    standartColor();
                    break;
                }
            }
            else {
                yellowColor();
                cout << "Ввведите целое число!" << endl;
                ClearInputBuffer();
                standartColor();
            }
        }
        
        
    }
    catch (sql::SQLException e) {
        redColor();
        std::cerr << "Ошибка: " << e.what() << endl;
        standartColor();
    }
}

void checkLogin(sql::Connection* conn, std::unique_ptr<player>& plr) {
    while (true) {
        std::string name, password;

        cout << "Введите Логин" << endl;
        cin >> name;

        std::unique_ptr<sql::PreparedStatement> login(conn->prepareStatement("SELECT * FROM players WHERE name = ?"));
        login->setString(1, name);
        std::unique_ptr<sql::ResultSet> rs(login->executeQuery());
        if (rs->next()) {
            cout << "Ваш логин найден! Введите пароль" << endl;
            cin >> password;

            if (password == std::string(rs->getString("password"))){
                plr = std::make_unique<player>(conn, name, password, "login");
                break;
            }
            else {
                yellowColor();
                cout << "Неправильный пароль!" << endl;
                ClearInputBuffer();
                standartColor();
                continue;
            }
        }
        else {
            yellowColor();
            cout << "Такого логина не существует!" << endl;
            standartColor();
            continue;
        }
    }

}
void checkRegister(sql::Connection* conn, std::unique_ptr<player>& plr) {
    std::string name, password;

    while (true) {
        cout << "Введите Логин" << endl;
        cin >> name;
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM players WHERE name = ?"));
        pstmt->setString(1, name);
        std::unique_ptr<sql::ResultSet> rs(pstmt->executeQuery());
        if (rs->next()) {
            yellowColor();
            cout << "Игрок с таким именем уже существует!" << endl;
            ClearInputBuffer();
            standartColor();
            continue;
        }
        else {
            break;
        }
    }


    cout << "Введите Пароль" << endl;
    cin >> password;

    plr = std::make_unique<player>(conn, name, password, "register");

}