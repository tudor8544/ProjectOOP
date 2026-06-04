#include "GUI.h"
#include <QString>

GUI::GUI(Controller* ctrl, QWidget* parent) : QWidget(parent) {
    this->ctrl = ctrl;
    initUI();
    connectSignalsAndSlots();
    populateList(this->ctrl->getAll()); // Load initial data
}

void GUI::initUI() {
    // Main layout (Left: List, Right: Controls)
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // --- LEFT SIDE: List ---
    QVBoxLayout* listLayout = new QVBoxLayout();
    listWidget = new QListWidget();
    listLayout->addWidget(new QLabel("Ice Cream Inventory:"));
    listLayout->addWidget(listWidget);
    mainLayout->addLayout(listLayout);

    // --- RIGHT SIDE: Controls ---
    QVBoxLayout* controlsLayout = new QVBoxLayout();

    // 1. Form Layout for Inputs
    QFormLayout* formLayout = new QFormLayout();
    idInput = new QLineEdit();
    nameInput = new QLineEdit();
    flavourInput = new QLineEdit();

    formLayout->addRow("ID:", idInput);
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Flavour:", flavourInput);
    controlsLayout->addLayout(formLayout);

    // 2. Action Buttons
    QHBoxLayout* actionButtonsLayout = new QHBoxLayout();
    btnAdd = new QPushButton("Add");
    btnRemove = new QPushButton("Remove");
    btnUpdate = new QPushButton("Update");
    actionButtonsLayout->addWidget(btnAdd);
    actionButtonsLayout->addWidget(btnRemove);
    actionButtonsLayout->addWidget(btnUpdate);
    controlsLayout->addLayout(actionButtonsLayout);

    // 3. Undo/Redo Buttons
    QHBoxLayout* undoRedoLayout = new QHBoxLayout();
    btnUndo = new QPushButton("Undo");
    btnRedo = new QPushButton("Redo");
    undoRedoLayout->addWidget(btnUndo);
    undoRedoLayout->addWidget(btnRedo);
    controlsLayout->addLayout(undoRedoLayout);

    // 4. Filtering Section
    QFormLayout* filterLayout = new QFormLayout();
    filterFlavourInput = new QLineEdit(this);
    filterNameInput = new QLineEdit(this);
    filterLayout->addRow("Filter by Flavour:", filterFlavourInput);
    filterLayout->addRow("Filter by Name:", filterNameInput);
    controlsLayout->addLayout(filterLayout);

    QGroupBox* filterTypeGroup = new QGroupBox("Search Logic", this);
    QHBoxLayout* radioLayout = new QHBoxLayout(filterTypeGroup);

    radioAnd = new QRadioButton("Match All (AND)", this);
    radioOr = new QRadioButton("Match Any (OR)", this);

    radioAnd->setChecked(true);

    radioLayout->addWidget(radioAnd);
    radioLayout->addWidget(radioOr);
    controlsLayout->addWidget(filterTypeGroup);


    QHBoxLayout* filterButtonsLayout = new QHBoxLayout();
    btnFilter = new QPushButton("Apply Filter", this);
    btnClearFilter = new QPushButton("Clear Filter", this);
    filterButtonsLayout->addWidget(btnFilter);
    filterButtonsLayout->addWidget(btnClearFilter);
    controlsLayout->addLayout(filterButtonsLayout);

    mainLayout->addLayout(controlsLayout);

    this->setWindowTitle("Ice Cream Shop Manager");
    this->resize(600, 400);
}

void GUI::connectSignalsAndSlots() {
    // Connect buttons to their respective functions
    connect(btnAdd, &QPushButton::clicked, this, &GUI::addHandler);
    connect(btnRemove, &QPushButton::clicked, this, &GUI::removeHandler);
    connect(btnUpdate, &QPushButton::clicked, this, &GUI::updateHandler);
    connect(btnUndo, &QPushButton::clicked, this, &GUI::undoHandler);
    connect(btnRedo, &QPushButton::clicked, this, &GUI::redoHandler);
    connect(btnFilter, &QPushButton::clicked, this, &GUI::filterHandler);
    connect(btnClearFilter, &QPushButton::clicked, this, &GUI::clearFilterHandler);

    // Auto-fill form when clicking an item in the list
    connect(listWidget, &QListWidget::itemSelectionChanged, this, &GUI::populateFormFromSelection);
}

void GUI::populateList(const vector<shared_ptr<IceCream>>& items) {
    listWidget->clear();
    for (const auto& ic : items) {
        QString itemText = QString("ID: %1 | Name: %2 | Flavour: %3")
                               .arg(ic->getID())
                               .arg(QString::fromStdString(ic->getNAME()))
                               .arg(QString::fromStdString(ic->getFLAVOUR()));
        listWidget->addItem(itemText);
    }
}

void GUI::addHandler() {
    int id = idInput->text().toInt();
    string name = nameInput->text().toStdString();
    string flavour = flavourInput->text().toStdString();

    ctrl->addIceCream(id, name, flavour);
    populateList(ctrl->getAll());
}

void GUI::removeHandler() {
    int id = idInput->text().toInt();
    ctrl->removeIceCream(id);
    populateList(ctrl->getAll());

    idInput->clear();
    nameInput->clear();
    flavourInput->clear();
}

void GUI::updateHandler() {
    int id = idInput->text().toInt();
    string name = nameInput->text().toStdString();
    string flavour = flavourInput->text().toStdString();

    ctrl->updateIceCream(id, name, flavour);
    populateList(ctrl->getAll());
}

void GUI::undoHandler() {
    ctrl->undo();
    populateList(ctrl->getAll());
}

void GUI::redoHandler() {
    ctrl->redo();
    populateList(ctrl->getAll());
}

void GUI::filterHandler() {
    string flavour = filterFlavourInput->text().toStdString();
    string name = filterNameInput->text().toStdString();

    // 1. If both are empty, reset
    if (flavour.empty() && name.empty()) {
        clearFilterHandler();
        return;
    }

    shared_ptr<Filter> activeFilter;

    // 2. Build filter based on inputs AND radio button selection
    if (!flavour.empty() && !name.empty()) {
        // Both fields have text: Check which radio button is selected
        shared_ptr<Filter> filter_flavour = make_shared<FlavourFilter>(flavour);
        shared_ptr<Filter> filter_name = make_shared<NameFilter>(name);

        if (radioAnd->isChecked()) {
            activeFilter = make_shared<AndFilter>(filter_name, filter_flavour);
        } else {
            // If it's not AND, it must be OR
            activeFilter = make_shared<OrFilter>(filter_name, filter_flavour);
        }
    }
    else if (!flavour.empty()) {
        // Only Flavour has text (AND/OR doesn't matter here)
        activeFilter = make_shared<FlavourFilter>(flavour);
    }
    else {
        // Only Name has text (AND/OR doesn't matter here)
        activeFilter = make_shared<NameFilter>(name);
    }

    // 3. Execute and populate
    vector<shared_ptr<IceCream>> filteredItems = ctrl->filter(activeFilter);
    populateList(filteredItems);
}

void GUI::clearFilterHandler() {
    filterFlavourInput->clear();
    filterNameInput->clear();
    populateList(ctrl->getAll());
}

void GUI::populateFormFromSelection() {
    if (listWidget->selectedItems().isEmpty()) return;

    // Basic string splitting to put data back into the form fields
    QString text = listWidget->selectedItems().first()->text();
    QStringList parts = text.split(" | ");

    if (parts.size() == 3) {
        idInput->setText(parts[0].replace("ID: ", ""));
        nameInput->setText(parts[1].replace("Name: ", ""));
        flavourInput->setText(parts[2].replace("Flavour: ", ""));
    }
}