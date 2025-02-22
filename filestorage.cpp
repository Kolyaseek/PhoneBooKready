#include "filestorage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

FileStorage::FileStorage(const QString &filename)
    : m_filename(filename) {}

void FileStorage::save(const PhoneBook &phoneBook) {
    QFile file(m_filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Contact &contact : phoneBook.contacts()) {
            out << contact.firstName() << ","
                << contact.lastName() << ","
                << contact.middleName() << ","
                << contact.address() << ","
                << contact.birthDate().toString("dd.MM.yyyy") << ","
                << contact.email() << ","
                << contact.phoneNumbers().join(";") << "\n";
        }
        file.close();
    } else {
        throw std::runtime_error("Не удалось открыть файл для записи!");
    }
}

PhoneBook FileStorage::load() {
    PhoneBook phoneBook;
    QFile file(m_filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 7) {
                QStringList phoneNumbers = parts[6].split(";");
                Contact contact(parts[0], parts[1], parts[2], parts[3], QDate::fromString(parts[4], "dd.MM.yyyy"), parts[5], phoneNumbers);
                if (contact.isValid()) {
                    phoneBook.addContact(contact);
                }
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Не удалось открыть файл для чтения!");
    }
    return phoneBook;
}
