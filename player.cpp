#include <iostream>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "inventory.h"
#include "colors.h"
#include "player.h"

using std::cout;
using std::endl;
using std::cin;

player::player(sql::Connection* conn, const std::string& n, const std::string& pass, const std::string& signType): 
	name(n), password(pass){
	try {
		if (signType == "register") {
			int health = 3;
			int chapter = 1;

			std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("INSERT INTO players (name, password, health, chapter) VALUES (?, ?, ?, ?)"));
			pstmt->setString(1, name);
			pstmt->setString(2, password);
			pstmt->setInt(3, health);
			pstmt->setInt(4, chapter);
			pstmt->executeUpdate();

			std::unique_ptr<sql::PreparedStatement> getId(conn->prepareStatement("SELECT id FROM players WHERE name = ?"));
			getId->setString(1, name);
			std::unique_ptr<sql::ResultSet> result(getId->executeQuery());
			if (result->next()) {
				id = result->getInt("id");
			}

		}
		else if (signType == "login") {
			std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM players WHERE name = ?"));
			pstmt->setString(1, name);
			std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());
			if (result->next()) {
				name = result->getString("name");
				password = result->getString("password");
				health = result->getInt("health");
				chapter = result->getInt("chapter");
				id = result->getInt("id");
			}
		}
		else {
			yellowColor();
			cout << "Такого типа не существует!" << endl;
			standartColor();
		}
	}
	catch (sql::SQLException e) {
		redColor();
		std::cerr << "Ошибка: " << e.what() << endl;
		standartColor();
	}

}

player::~player() {

}

void player::getDamage(sql::Connection* conn, int quanity) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(""));
	}
	catch (sql::SQLException e) {
		redColor();
		std::cerr << "Ошибка: " << e.what() << endl;
		standartColor();
	}
}