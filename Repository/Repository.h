//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#ifndef PROIECTOOP_REPOSITORY_H
#define PROIECTOOP_REPOSITORY_H
#include <vector>
#include "../Domain/IceCream.h"

class Repository {
public:
    virtual ~Repository() = default;
    virtual void add(shared_ptr<IceCream> icecream) = 0;
    virtual void remove(int id) = 0;
    virtual vector<shared_ptr<IceCream>>& getAll()  = 0;
    virtual int find_index(int id) = 0;


};


#endif //PROIECTOOP_REPOSITORY_H