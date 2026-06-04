//
// Created by Muraru Tudor Vlad on 30/05/2026.
//

#ifndef PROIECTOOP_ICECREAM_H
#define PROIECTOOP_ICECREAM_H
#include <iostream>
using namespace std;

class IceCream {

private:
    int id;
    string name;
    string flavour;

public:
    IceCream(int id, string name, string flavour);
    int getID() const;
    string getNAME() const;
    string getFLAVOUR() const;
    friend ostream& operator<<(ostream& os, const IceCream& icecream);




};


#endif //PROIECTOOP_ICECREAM_H