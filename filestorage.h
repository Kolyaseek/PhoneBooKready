#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "phonebook.h"
#include <QString>

class FileStorage {
public:
    FileStorage(const QString &filename);

    void save(const PhoneBook &phoneBook);
    PhoneBook load();

private:
    QString m_filename;
};

#endif // FILESTORAGE_H
