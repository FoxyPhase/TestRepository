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

void inventory::addItem(sql::Connection* conn, int plr_id, const std::string& name) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM items WHERE name = ?"));
		pstmt->setString(1, name);

		std::unique_ptr<sql::ResultSet> result(pstmt->executeQuery());
		if (result->next()) {
			std::unique_ptr<sql::PreparedStatement> inventoryAdd(conn->prepareStatement("INSERT INTO inventory (player_id, item_name, item_description, canUse) VALUES (?,?,?,?)"));
			inventoryAdd->setInt(1, plr_id);
			inventoryAdd->setString(2, result->getString("name"));
			inventoryAdd->setString(3, result->getString("description"));
			inventoryAdd->setInt(4, result->getInt("canUse"));

			inventoryAdd->executeUpdate();

			item newItem{
				result->getString("name"),
				result->getString("description"),
				result->getInt("canUse")
			};
			Items.push_back(newItem);
		}
		else {
			yellowColor();
			cout << "��� ������� �� ������ ��� ��� �� ����������!" << endl;
			standartColor();
		}
	}
	catch (sql::SQLException e) {
		redColor();
		std::cerr << "������: " << e.what() << endl;
		standartColor();
	}
}

//������� ������� � ��������� � ��
void inventory::delItem(sql::Connection* conn, int plr_id, const std::string& name) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("DELETE FROM inventory WHERE player_id = ? AND item_name = ?"));
		pstmt->setInt(1, plr_id);
		pstmt->setString(2, name);
		pstmt->executeUpdate();
		Items.erase(std::remove_if(Items.begin(), Items.end(),
			[&](const item& it) { return it.name == name; }),
			Items.end());

	}
	catch (sql::SQLException e) {
		redColor();
		std::cerr << "������ �������� ��������: " << e.what() << endl;
		standartColor();
	}
}

//�������� ��������� ��� ������� ����
void inventory::loadInventory(sql::Connection* conn, int player_id) {
	try {
		std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM inventory WHERE player_id = ?"));
		pstmt->setInt(1, player_id);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

		Items.clear();  // ������� ������ ����� ���������

		while (res->next()) {  // ���������� ������ ���� ����
			item newItem;
			newItem.name = res->getString("item_name");  // ����������� ���������� ����� �������
			newItem.description = res->getString("item_description");
			newItem.canUse = res->getInt("canUse");
			Items.push_back(newItem);

			greenColor();
			cout << "������� ����� � �� �������: " << newItem.name << endl;
			standartColor();
		}

		if (Items.empty()) {
			yellowColor();
			cout << "��� ��������� ��� ����" << endl;
			standartColor();
		}
	}
	catch (sql::SQLException& e) {
		std::cerr << "������ �������� ���������: " << e.what() << std::endl;
	}
}
