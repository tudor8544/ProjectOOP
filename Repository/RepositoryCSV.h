//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#ifndef PROIECTOOP_REPOSITORYCSV_H
#define PROIECTOOP_REPOSITORYCSV_H
#include "../Repository/Repository.h"

class RepositoryCSV : public Repository{
private:
    string fileName;
    vector<shared_ptr<IceCream>> ice_creams;
    void loadFromFile();
    void saveToFile();
public:
    RepositoryCSV(const string& fileName);
    void add(shared_ptr<IceCream> icecream) override;
    void remove(int id) override;
    vector<shared_ptr<IceCream>>& getAll() override;
    int find_index(int id) override;

};


#endif //PROIECTOOP_REPOSITORYCSV_H