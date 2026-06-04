#include "Command.h"

AddCommand::AddCommand(Repository* repo, shared_ptr<IceCream> icecream) {
    this->repo = repo;
    this->icecream = icecream;
}

void AddCommand::execute() {
    // O(1)
    repo->add(icecream);
}

void AddCommand::undo() {
    // O(N)
    repo->remove(icecream->getID());
}

RemoveCommand::RemoveCommand(Repository* repo, shared_ptr<IceCream> icecream) {
    this->repo = repo;
    this->icecream = icecream;
}

void RemoveCommand::execute() {
    // O(N)
    repo->remove(icecream->getID());
}

void RemoveCommand::undo() {
    // O(1)
    repo->add(icecream);
}

UpdateCommand::UpdateCommand(Repository* repo, shared_ptr<IceCream> oldIcecream, shared_ptr<IceCream> newIcecream) {
    this->repo = repo;
    this->oldIcecream = oldIcecream;
    this->newIcecream = newIcecream;
}

void UpdateCommand::execute() {
    // O(N)
    repo->remove(oldIcecream->getID());
    repo->add(newIcecream);
}

void UpdateCommand::undo() {
    // O(N)
    repo->remove(newIcecream->getID());
    repo->add(oldIcecream);
}