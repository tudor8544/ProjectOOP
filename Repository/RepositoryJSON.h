//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#ifndef PROIECTOOP_REPOSITORYJSON_H
#define PROIECTOOP_REPOSITORYJSON_H
#include "../Repository/Repository.h"
#include <QString>

class RepositoryJSON : public Repository{
private:
    QString fileName;
    vector<shared_ptr<IceCream>> ice_creams;
    void loadFromFile();
    void saveToFile();
public:
    RepositoryJSON(const QString& fileName);
    void add(shared_ptr<IceCream> icecream) override;
    void remove(int id) override;
    vector<shared_ptr<IceCream>>& getAll() override;
    int find_index(int id) override;
};


#endif //PROIECTOOP_REPOSITORYJSON_H