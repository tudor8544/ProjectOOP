#ifndef PROIECTOOP_CONTROLLER_H
#define PROIECTOOP_CONTROLLER_H

#include <vector>
#include <memory>
#include "../Repository/Repository.h"
#include "Command.h"
#include "Filter.h"

class Controller {
private:
    Repository* repo;
    vector<shared_ptr<Command>> undoStack;
    vector<shared_ptr<Command>> redoStack;

public:
    Controller(Repository* repo);

    void addIceCream(int id, const string& name, const string& flavour);
    void removeIceCream(int id);
    void updateIceCream(int id, const string& newName, const string& newFlavour);

    void undo();
    void redo();

    vector<shared_ptr<IceCream>> filter(shared_ptr<Filter> criteria);
    vector<shared_ptr<IceCream>>& getAll();
};

#endif