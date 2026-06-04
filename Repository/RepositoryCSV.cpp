//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#include "RepositoryCSV.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>

RepositoryCSV::RepositoryCSV(const string& fileName) {
    this -> fileName = fileName;
};
void RepositoryCSV::add(shared_ptr<IceCream> icecream) {
    ice_creams.push_back(icecream);
    saveToFile();

};
int RepositoryCSV::find_index(int id) {
    for(auto i= 0; i< ice_creams.size(); i++) {
        if(ice_creams[i]->getID() == id) {
            return i;
        }

    }
    return -1;
};

void RepositoryCSV::remove(int id) {
    int index = find_index(id);
    if(index == -1) {
        throw runtime_error("No such ID");
    }
    ice_creams.erase(ice_creams.begin() + index);
    saveToFile();

};

vector<shared_ptr<IceCream>>& RepositoryCSV::getAll() {
    return ice_creams;
};

void RepositoryCSV::loadFromFile() {
    ifstream file(fileName);
    string line, idStr, name, flavour;

    ice_creams.clear();

    while(getline(file, line)) {
        stringstream ss(line);

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, flavour, ',');

        if(!idStr.empty()) {
            int id = stoi(idStr);
            ice_creams.push_back(make_shared<IceCream>(id, name, flavour));
        }
    }
    file.close();
};

void RepositoryCSV::saveToFile() {
    ofstream file(fileName);

    for(int i = 0; i < ice_creams.size(); i++) {
        file << ice_creams[i]->getID() << ", "<< ice_creams[i]->getNAME()<< ", "<< ice_creams[i]-> getFLAVOUR()<<"\n";
    }
    file.close();
};