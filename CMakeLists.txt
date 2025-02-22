cmake_minimum_required(VERSION 3.14)
project(PhoneBook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # Включаем автоматическую обработку .ui файлов

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# Указываем исходные файлы
set(SOURCES
    main.cpp
    mainwindow.cpp
    contact.cpp
    phonebook.cpp
    filestorage.cpp
    databasestorage.cpp
)

# Указываем .ui файл
set(UI_FILES
    mainwindow.ui
)

# Создаем исполняемый файл
add_executable(PhoneBook ${SOURCES} ${UI_FILES})

# Подключаем необходимые библиотеки
target_link_libraries(PhoneBook PRIVATE Qt6::Widgets Qt6::Sql)
