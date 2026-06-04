//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#include "RepositoryJSON.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RepositoryJSON::RepositoryJSON(const QString& fileName) {
    this -> fileName = fileName;
}

int RepositoryJSON::find_index(int id) {
    for(int i= 0; i< ice_creams.size(); i++) {
        if(ice_creams[i]-> getID() == id) {
            return id;
        }
    }
    return -1;
}

void RepositoryJSON::add(shared_ptr<IceCream> icecream) {
    ice_creams.push_back(icecream);
    saveToFile();
}

void RepositoryJSON::remove(int id) {
    int index = find_index(id);
    if(index == -1) {
        throw runtime_error("No such ID");
    }
    ice_creams.erase(ice_creams.begin() + index);
    saveToFile();
}

vector<shared_ptr<IceCream>>& RepositoryJSON::getAll() {
    return ice_creams;
}

void RepositoryJSON:: loadFromFile() {
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray array = doc.array();

    ice_creams.clear();

    for(int i = 0; i<array.size(); i++) {
        QJsonObject obj = array[i].toObject();
        int id = obj["id"].toInt();
        string name = obj["name"].toString().toStdString();
        string flavour = obj["flavour"].toString().toStdString();

        ice_creams.push_back(make_shared<IceCream>(id, name, flavour));
    }
    file.close();
}

void RepositoryJSON:: saveToFile() {
    QJsonArray array;

    for(int i =0; i< ice_creams.size(); i++) {
        QJsonObject obj;
        obj["id"] = ice_creams[i]->getID();
        obj["name"] = QString::fromStdString(ice_creams[i]->getNAME());
        obj["flavour"] = QString::fromStdString(ice_creams[i]->getFLAVOUR());

        array.append(obj);
    }
    QJsonDocument doc(array);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
    }
    file.close();
}