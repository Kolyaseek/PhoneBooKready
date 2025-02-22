#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>
#include <QList>
#include <QRegularExpression>

class Contact {
public:
    Contact();
    Contact(const QString &firstName, const QString &lastName, const QString &middleName,
            const QString &address, const QDate &birthDate, const QString &email,
            const QList<QString> &phoneNumbers);

    QString firstName() const;
    void setFirstName(const QString &firstName);

    QString lastName() const;
    void setLastName(const QString &lastName);

    QString middleName() const;
    void setMiddleName(const QString &middleName);

    QString address() const;
    void setAddress(const QString &address);

    QDate birthDate() const;
    void setBirthDate(const QDate &birthDate);

    QString email() const;
    void setEmail(const QString &email);

    QList<QString> phoneNumbers() const;
    void setPhoneNumbers(const QList<QString> &phoneNumbers);

    bool isValid() const;

private:
    QString m_firstName;
    QString m_lastName;
    QString m_middleName;
    QString m_address;
    QDate m_birthDate;
    QString m_email;
    QList<QString> m_phoneNumbers;
};

#endif // CONTACT_H
