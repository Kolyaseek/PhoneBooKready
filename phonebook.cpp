#include "phonebook.h"
#include <algorithm>

PhoneBook::PhoneBook() {}

void PhoneBook::addContact(const Contact &contact) {
    if (contact.isValid()) {
        m_contacts.append(contact);
    }
}

void PhoneBook::removeContact(int index) {
    if (index >= 0 && index < m_contacts.size()) {
        m_contacts.removeAt(index);
    }
}

void PhoneBook::editContact(int index, const Contact &contact) {
    if (index >= 0 && index < m_contacts.size() && contact.isValid()) {
        m_contacts[index] = contact;
    }
}

QList<Contact> PhoneBook::contacts() const {
    return m_contacts;
}

void PhoneBook::sortByFirstName() {
    std::sort(m_contacts.begin(), m_contacts.end(), [](const Contact &a, const Contact &b) {
        return a.firstName() < b.firstName();
    });
}

void PhoneBook::sortByLastName() {
    std::sort(m_contacts.begin(), m_contacts.end(), [](const Contact &a, const Contact &b) {
        return a.lastName() < b.lastName();
    });
}

void PhoneBook::sortByBirthDate() {
    std::sort(m_contacts.begin(), m_contacts.end(), [](const Contact &a, const Contact &b) {
        return a.birthDate() < b.birthDate();
    });
}

QList<Contact> PhoneBook::search(const QString &query) const {
    QList<Contact> result;
    for (const Contact &contact : m_contacts) {
        if (contact.firstName().contains(query, Qt::CaseInsensitive) ||
            contact.lastName().contains(query, Qt::CaseInsensitive) ||
            contact.middleName().contains(query, Qt::CaseInsensitive) ||
            contact.email().contains(query, Qt::CaseInsensitive) ||
            contact.phoneNumbers().contains(query)) {
            result.append(contact);
        }
    }
    return result;
}
