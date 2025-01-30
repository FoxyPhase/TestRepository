#include <iostream>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include "items.h"
#include "colors.h"

item::item() {

}

item::~item() {

}

void item::showAllItems(sql::Connection* conn) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM items"));
		std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());
		while (result->next()) {
			std::cout << "ID: " << result->getInt("id") << std::endl;
			std::cout << "Название предмета: " << result->getString("name") << std::endl;
			std::cout << "Описание предмета: " << result->getString("description") << std::endl;
			std::cout << "Можно ли использовать: " << (result->getBoolean("canUse") ? "True" : "False") << std::endl;
			std::cout << "----------------------------------------------------------------------" << std::endl;
		}
	}
	catch(sql::SQLException e){
		redColor();
		std::cout << "Ошибка: " << e.what() << std::endl;
		standartColor();
	}
}