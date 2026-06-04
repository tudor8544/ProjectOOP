#ifndef PROIECTOOP_GUI_H
#define PROIECTOOP_GUI_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include "../Controller/Controller.h"
#include <QRadioButton>
#include <QGroupBox>

class GUI : public QWidget {
    Q_OBJECT

private:
    Controller* ctrl;

    // UI Components
    QListWidget* listWidget;

    // Input Fields
    QLineEdit* idInput;
    QLineEdit* nameInput;
    QLineEdit* flavourInput;

    // Filter Input
    QLineEdit* filterFlavourInput;
    QLineEdit* filterNameInput;


    // Buttons
    QPushButton* btnAdd;
    QPushButton* btnRemove;
    QPushButton* btnUpdate;
    QPushButton* btnUndo;
    QPushButton* btnRedo;
    QPushButton* btnFilter;
    QPushButton* btnClearFilter;
    QRadioButton* radioAnd;
    QRadioButton* radioOr;

    // Setup Methods
    void initUI();
    void connectSignalsAndSlots();
    void populateList(const vector<shared_ptr<IceCream>>& items);

private slots:
    void addHandler();
    void removeHandler();
    void updateHandler();
    void undoHandler();
    void redoHandler();
    void filterHandler();
    void clearFilterHandler();
    void populateFormFromSelection();

public:
    GUI(Controller* ctrl, QWidget* parent = nullptr);
};

#endif //PROIECTOOP_GUI_H