#include "databasestorage.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

DatabaseStorage::DatabaseStorage(const QString &databaseName) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(databaseName);

    if (!m_db.open()) {
        throw std::runtime_error("Не удалось открыть базу данных!");
    }

    createTable();
}

DatabaseStorage::~DatabaseStorage() {
    m_db.close();
}

void DatabaseStorage::createTable() {
    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS contacts ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "first_name TEXT NOT NULL, "
                  "last_name TEXT NOT NULL, "
                  "middle_name TEXT, "
                  "address TEXT, "
                  "birth_date TEXT, "
                  "email TEXT, "
                  "phone_numbers TEXT)");

    if (!query.exec()) {
        throw std::runtime_error("Не удалось создать таблицу: " + query.lastError().text().toStdString());
    }
}

void DatabaseStorage::save(const PhoneBook &phoneBook) {
    QSqlQuery query;
    query.prepare("DELETE FROM contacts");
    if (!query.exec()) {
        throw std::runtime_error("Не удалось очистить таблицу: " + query.lastError().text().toStdString());
    }

    for (const Contact &contact : phoneBook.contacts()) {
        query.prepare("INSERT INTO contacts (first_name, last_name, middle_name, address, birth_date, email, phone_numbers) "
                      "VALUES (:first_name, :last_name, :middle_name, :address, :birth_date, :email, :phone_numbers)");
        query.bindValue(":first_name", contact.firstName());
        query.bindValue(":last_name", contact.lastName());
        query.bindValue(":middle_name", contact.middleName());
        query.bindValue(":address", contact.address());
        query.bindValue(":birth_date", contact.birthDate().toString("yyyy-MM-dd"));
        query.bindValue(":email", contact.email());
        query.bindValue(":phone_numbers", contact.phoneNumbers().join(";"));

        if (!query.exec()) {
            throw std::runtime_error("Не удалось вставить контакт: " + query.lastError().text().toStdString());
        }
    }
}

PhoneBook DatabaseStorage::load() {
    PhoneBook phoneBook;
    QSqlQuery query("SELECT * FROM contacts");

    while (query.next()) {
        QString firstName = query.value("first_name").toString();
        QString lastName = query.value("last_name").toString();
        QString middleName = query.value("middle_name").toString();
        QString address = query.value("address").toString();
        QDate birthDate = QDate::fromString(query.value("birth_date").toString(), "yyyy-MM-dd");
        QString email = query.value("email").toString();
        QStringList phoneNumbers = query.value("phone_numbers").toString().split(";");

        Contact contact(firstName, lastName, middleName, address, birthDate, email, phoneNumbers);
        if (contact.isValid()) {
            phoneBook.addContact(contact);
        }
    }

    return phoneBook;
}
