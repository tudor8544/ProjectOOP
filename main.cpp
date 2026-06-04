#include <QApplication>
#include "Repository/RepositoryJSON.h" // Or RepositoryCSV.h
#include "Controller/Controller.h"
#include "UI/GUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Initialize the layers
    RepositoryJSON* repo = new RepositoryJSON("data.json");
    Controller* ctrl = new Controller(repo);
    GUI* gui = new GUI(ctrl);

    gui->show();

    int result = QApplication::exec();

    // Clean up memory
    delete gui;
    delete ctrl;
    delete repo;

    return result;
}