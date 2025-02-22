#include "contact.h"

Contact::Contact() {}

Contact::Contact(const QString &firstName, const QString &lastName, const QString &middleName,
                 const QString &address, const QDate &birthDate, const QString &email,
                 const QList<QString> &phoneNumbers)
    : m_firstName(firstName.trimmed()), m_lastName(lastName.trimmed()), m_middleName(middleName.trimmed()),
      m_address(address.trimmed()), m_birthDate(birthDate), m_email(email.trimmed()), m_phoneNumbers(phoneNumbers) {}

QString Contact::firstName() const {
    return m_firstName;
}

void Contact::setFirstName(const QString &firstName) {
    m_firstName = firstName.trimmed();
}

QString Contact::lastName() const {
    return m_lastName;
}

void Contact::setLastName(const QString &lastName) {
    m_lastName = lastName.trimmed();
}

QString Contact::middleName() const {
    return m_middleName;
}

void Contact::setMiddleName(const QString &middleName) {
    m_middleName = middleName.trimmed();
}

QString Contact::address() const {
    return m_address;
}

void Contact::setAddress(const QString &address) {
    m_address = address.trimmed();
}

QDate Contact::birthDate() const {
    return m_birthDate;
}

void Contact::setBirthDate(const QDate &birthDate) {
    m_birthDate = birthDate;
}

QString Contact::email() const {
    return m_email;
}

void Contact::setEmail(const QString &email) {
    m_email = email.trimmed();
}

QList<QString> Contact::phoneNumbers() const {
    return m_phoneNumbers;
}

void Contact::setPhoneNumbers(const QList<QString> &phoneNumbers) {
    m_phoneNumbers = phoneNumbers;
}

bool Contact::isValid() const {
    QRegularExpression nameRegex("^[A-Za-zА-Яа-я][A-Za-zА-Яа-я\\s\\-]*[A-Za-zА-Яа-я]$");
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpression phoneRegex("^(\\+7|8)[\\(\\s]?\\d{3}[\\)\\s]?\\d{3}[\\-\\s]?\\d{2}[\\-\\s]?\\d{2}$");

    if (!nameRegex.match(m_firstName).hasMatch() ||
        !nameRegex.match(m_lastName).hasMatch() ||
        !nameRegex.match(m_middleName).hasMatch()) {
        return false;
    }

    if (!emailRegex.match(m_email).hasMatch()) {
        return false;
    }

    for (const QString &phone : m_phoneNumbers) {
        if (!phoneRegex.match(phone).hasMatch()) {
            return false;
        }
    }

    return true;
}
