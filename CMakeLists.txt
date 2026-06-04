cmake_minimum_required(VERSION 4.1)
project(ProiectOOP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/Users/murarutudorvlad/Qt/6.11.1/macos")


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ProiectOOP main.cpp
        Domain/IceCream.cpp
        Domain/IceCream.h
        Repository/Repository.cpp
        Repository/Repository.h
        Repository/RepositoryCSV.cpp
        Repository/RepositoryCSV.h
        Repository/RepositoryJSON.cpp
        Repository/RepositoryJSON.h
        Controller/Filter.cpp
        Controller/Filter.h
        Controller/Command.cpp
        Controller/Command.h
        Controller/Controller.cpp
        Controller/Controller.h
        UI/GUI.cpp
        UI/GUI.h)
target_link_libraries(ProiectOOP
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

