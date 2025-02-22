#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "contact.h"
#include <QList>

class PhoneBook {
public:
    PhoneBook();

    void addContact(const Contact &contact);
    void removeContact(int index);
    void editContact(int index, const Contact &contact);
    QList<Contact> contacts() const;
    void sortByFirstName();
    void sortByLastName();
    void sortByBirthDate();
    QList<Contact> search(const QString &query) const;

private:
    QList<Contact> m_contacts;
};

#endif // PHONEBOOK_H
