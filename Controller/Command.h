#ifndef PROIECTOOP_COMMAND_H
#define PROIECTOOP_COMMAND_H

#include <memory>
#include "../Repository/Repository.h"
#include "../Domain/IceCream.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddCommand : public Command {
private:
    Repository* repo;
    shared_ptr<IceCream> icecream;
public:
    AddCommand(Repository* repo, shared_ptr<IceCream> icecream);
    void execute() override;
    void undo() override;
};

class RemoveCommand : public Command {
private:
    Repository* repo;
    shared_ptr<IceCream> icecream;
public:
    RemoveCommand(Repository* repo, shared_ptr<IceCream> icecream);
    void execute() override;
    void undo() override;
};

class UpdateCommand : public Command {
private:
    Repository* repo;
    shared_ptr<IceCream> oldIcecream;
    shared_ptr<IceCream> newIcecream;
public:
    UpdateCommand(Repository* repo, shared_ptr<IceCream> oldIcecream, shared_ptr<IceCream> newIcecream);
    void execute() override;
    void undo() override;
};

#endif