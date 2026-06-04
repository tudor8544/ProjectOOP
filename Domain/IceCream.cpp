//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#include "IceCream.h"


IceCream::IceCream(int id, string name, string flavour) {
    this -> id = id;
    this -> name = name;
    this -> flavour = flavour;
};

int IceCream::getID() const {
    return id;
}
;
string IceCream::getNAME() const {
    return name;
};
string IceCream::getFLAVOUR() const {
    return flavour;
};
ostream& operator<<(ostream& os, const IceCream& icecream) {
    os << "Id : " << icecream.id << " "<< "Name : "<< icecream.name << " "<< "Flavour: "<< icecream.flavour<<endl;
   return os;
};

