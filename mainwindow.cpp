#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contact.h"
#include "filestorage.h"
#include "databasestorage.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddContact);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveContact);
    //connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::onEditContact);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(ui->sortFirstNameButton, &QPushButton::clicked, this, &MainWindow::onSortByFirstName);
    connect(ui->sortLastNameButton, &QPushButton::clicked, this, &MainWindow::onSortByLastName);
    connect(ui->sortBirthDateButton, &QPushButton::clicked, this, &MainWindow::onSortByBirthDate);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"Имя", "Фамилия", "Отчество", "Адрес", "Дата рождения", "Email", "Телефоны"});
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    updateTable();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onAddContact() {
    QString firstName = ui->firstNameEdit->text();
    QString lastName = ui->lastNameEdit->text();
    QString middleName = ui->middleNameEdit->text();
    QString address = ui->addressEdit->text();
    QDate birthDate = ui->birthDateEdit->date();
    QString email = ui->emailEdit->text();
    QStringList phoneNumbers = ui->phoneNumbersEdit->text().split(",", Qt::SkipEmptyParts);

    Contact newContact(firstName, lastName, middleName, address, birthDate, email, phoneNumbers);

    if (newContact.isValid()) {
        m_phoneBook.addContact(newContact);
        updateTable();
        clearInputFields();
    } else {
        QMessageBox::warning(this, "Ошибка", "Некорректные данные контакта!");
    }
}

void MainWindow::onRemoveContact() {
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0) {
        m_phoneBook.removeContact(selectedRow);
        updateTable();
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для удаления!");
    }
}
/*
void MainWindow::onEditContact() {
    int selectedRow = ui->tableWidget->currentRow();
    if (selectedRow >= 0) {
        QString firstName = ui->firstNameEdit->text();
        QString lastName = ui->lastNameEdit->text();
        QString middleName = ui->middleNameEdit->text();
        QString address = ui->addressEdit->text();
        QDate birthDate = ui->birthDateEdit->date();
        QString email = ui->emailEdit->text();
        QStringList phoneNumbers = ui->phoneNumbersEdit->text().split(",", Qt::SkipEmptyParts);

        Contact updatedContact(firstName, lastName, middleName, address, birthDate, email, phoneNumbers);

        if (updatedContact.isValid()) {
            m_phoneBook.editContact(selectedRow, updatedContact);
            updateTable();
            clearInputFields();
        } else {
            QMessageBox::warning(this, "Ошибка", "Некорректные данные контакта!");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования!");
    }
}
*/
void MainWindow::onEditContact() {
    // Получаем индекс выбранной строки в таблице
    int selectedRow = ui->tableWidget->currentRow();

    if (selectedRow >= 0) {
        // Получаем данные из полей ввода
        QString firstName = ui->firstNameEdit->text();
        QString lastName = ui->lastNameEdit->text();
        QString middleName = ui->middleNameEdit->text();
        QString address = ui->addressEdit->text();
        QDate birthDate = ui->birthDateEdit->date();
        QString email = ui->emailEdit->text();
        QStringList phoneNumbers = ui->phoneNumbersEdit->text().split(",", Qt::SkipEmptyParts);

        // Создаем объект Contact с обновленными данными
        Contact updatedContact(firstName, lastName, middleName, address, birthDate, email, phoneNumbers);

        // Проверяем, что данные корректны
        if (updatedContact.isValid()) {
            // Обновляем контакт в PhoneBook
            m_phoneBook.editContact(selectedRow, updatedContact);

            // Обновляем таблицу
            updateTable();

            // Очищаем поля ввода
            clearInputFields();
        } else {
            QMessageBox::warning(this, "Ошибка", "Некорректные данные контакта!");
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования!");
    }
}

void MainWindow::onSearch() {
    QString query = ui->searchEdit->text();
    QList<Contact> results = m_phoneBook.search(query);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(results.size());

    int row = 0;
    for (const Contact &contact : results) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(contact.firstName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(contact.lastName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(contact.middleName()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(contact.address()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(contact.birthDate().toString("dd.MM.yyyy")));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(contact.email()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(contact.phoneNumbers().join(", ")));
        row++;
    }
}

void MainWindow::onSortByFirstName() {
    m_phoneBook.sortByFirstName();
    updateTable();
}

void MainWindow::onSortByLastName() {
    m_phoneBook.sortByLastName();
    updateTable();
}

void MainWindow::onSortByBirthDate() {
    m_phoneBook.sortByBirthDate();
    updateTable();
}

void MainWindow::onSaveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить данные", "", "Текстовые файлы (*.txt);;Базы данных SQLite (*.db)");
    if (fileName.isEmpty()) return;

    try {
        if (fileName.endsWith(".db")) {
            DatabaseStorage storage(fileName);
            storage.save(m_phoneBook);
        } else {
            FileStorage storage(fileName);
            storage.save(m_phoneBook);
        }
        QMessageBox::information(this, "Успех", "Данные успешно сохранены!");
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::onLoadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть данные", "", "Текстовые файлы (*.txt);;Базы данных SQLite (*.db)");
    if (fileName.isEmpty()) return;

    try {
        if (fileName.endsWith(".db")) {
            DatabaseStorage storage(fileName);
            m_phoneBook = storage.load();
        } else {
            FileStorage storage(fileName);
            m_phoneBook = storage.load();
        }
        updateTable();
        QMessageBox::information(this, "Успех", "Данные успешно загружены!");
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void MainWindow::updateTable() {
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(m_phoneBook.contacts().size());

    int row = 0;
    for (const Contact &contact : m_phoneBook.contacts()) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(contact.firstName()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(contact.lastName()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(contact.middleName()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(contact.address()));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(contact.birthDate().toString("dd.MM.yyyy")));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(contact.email()));
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(contact.phoneNumbers().join(", ")));
        row++;
    }
}

void MainWindow::clearInputFields() {
    ui->firstNameEdit->clear();
    ui->lastNameEdit->clear();
    ui->middleNameEdit->clear();
    ui->addressEdit->clear();
    ui->birthDateEdit->setDate(QDate::currentDate());
    ui->emailEdit->clear();
    ui->phoneNumbersEdit->clear();
}
