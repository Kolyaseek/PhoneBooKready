#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "phonebook.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddContact();
    void onRemoveContact();
    void onEditContact();
    void onSearch();
    void onSortByFirstName();
    void onSortByLastName();
    void onSortByBirthDate();
    void onSaveToFile();
    void onLoadFromFile();

private:
    Ui::MainWindow *ui;
    PhoneBook m_phoneBook;
    void updateTable();
    void clearInputFields();
};

#endif // MAINWINDOW_H
