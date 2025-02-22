#ifndef DATABASESTORAGE_H
#define DATABASESTORAGE_H

#include "phonebook.h"
#include <QString>
#include <QtSql/QSqlDatabase>

class DatabaseStorage {
public:
    DatabaseStorage(const QString &databaseName);
    ~DatabaseStorage();

    void save(const PhoneBook &phoneBook);
    PhoneBook load();

private:
    QSqlDatabase m_db;

    void createTable();
};

#endif // DATABASESTORAGE_H
