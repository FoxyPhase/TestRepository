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

using std::cout;
using std::endl;
using std::cin;

inventory::inventory() {

}

inventory::~inventory() {

}

void inventory::addItem(sql::Connection* conn, const std::string& name) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM items WHERE name = ?"));
		pstmt->setString(1, name);

		std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());
		if (result->next()) {
			item newItem{
				result->getString("name"),
				result->getString("description"),
				result->getInt("canUse")
			};
			Items.push_back(newItem);
		}
		else {
			yellowColor();
			cout << "Ваш предмет не найден или его не существует!" << endl;
			standartColor();
		}
	}
	catch (sql::SQLException e) {
		redColor();
		std::cerr << "Ошибка: " << e.what() << endl;
		standartColor();
	}
}

void inventory::delItem() {
	if (Items.size() > 0 ) {
		int choose;

		cout << "Какой предмет вы хотите удалить?" << endl;
		for (int i = 0; i < Items.size(); i++) {
			cout << i << ": " << Items.at(i).name << endl;
		}
		cin >> choose;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			redColor();
			cout << "Введите целое число!" << endl;
			standartColor();
		}
		else {
			if (choose >= 0 && choose < Items.size()) {
				Items.erase(Items.begin() + choose);
			}
			else {
				redColor();
				cout << "Неверный индекс предмета!" << endl;
				standartColor();
			}
		}
	}
	else {
		yellowColor();
		cout << "Ваш инвентарь пустой!" << endl;
		standartColor();
	}
}