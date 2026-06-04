#include "Controller.h"

Controller::Controller(Repository* repo) {
    this->repo = repo;
}

void Controller::addIceCream(int id, const string& name, const string& flavour) {
    // O(1)
    shared_ptr<IceCream> ic = make_shared<IceCream>(id, name, flavour);
    shared_ptr<Command> cmd = make_shared<AddCommand>(repo, ic);
    cmd->execute();
    undoStack.push_back(cmd);
    redoStack.clear();
}

void Controller::removeIceCream(int id) {
    // O(N)
    shared_ptr<IceCream> toRemove = nullptr;
    for (const auto& ic : repo->getAll()) {
        if (ic->getID() == id) {
            toRemove = ic;
            break;
        }
    }

    if (toRemove != nullptr) {
        shared_ptr<Command> cmd = make_shared<RemoveCommand>(repo, toRemove);
        cmd->execute();
        undoStack.push_back(cmd);
        redoStack.clear();
    }
}

void Controller::updateIceCream(int id, const string& newName, const string& newFlavour) {
    // O(N)
    shared_ptr<IceCream> oldIceCream = nullptr;
    for (const auto& ic : repo->getAll()) {
        if (ic->getID() == id) {
            oldIceCream = ic;
            break;
        }
    }

    if (oldIceCream != nullptr) {
        shared_ptr<IceCream> newIceCream = make_shared<IceCream>(id, newName, newFlavour);
        shared_ptr<Command> cmd = make_shared<UpdateCommand>(repo, oldIceCream, newIceCream);
        cmd->execute();
        undoStack.push_back(cmd);
        redoStack.clear();
    }
}

void Controller::undo() {
    // O(N)
    if (!undoStack.empty()) {
        shared_ptr<Command> cmd = undoStack.back();
        cmd->undo();
        undoStack.pop_back();
        redoStack.push_back(cmd);
    }
}

void Controller::redo() {
    // O(N)
    if (!redoStack.empty()) {
        shared_ptr<Command> cmd = redoStack.back();
        cmd->execute();
        redoStack.pop_back();
        undoStack.push_back(cmd);
    }
}

vector<shared_ptr<IceCream>> Controller::filter(shared_ptr<Filter> criteria) {
    // O(N)
    vector<shared_ptr<IceCream>> result;
    for (const auto& ic : repo->getAll()) {
        if (criteria->evaluate(*ic)) {
            result.push_back(ic);
        }
    }
    return result;
}

vector<shared_ptr<IceCream>>& Controller::getAll() {
    // O(1)
    return repo->getAll();
}