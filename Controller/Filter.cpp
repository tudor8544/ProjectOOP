#include "Filter.h"

FlavourFilter::FlavourFilter(const string& flavour) {
    this->flavour = flavour;
}

bool FlavourFilter::evaluate(const IceCream& icecream) const {
    // O(1)
    return icecream.getFLAVOUR() == flavour;
}

NameFilter::NameFilter(const string& name) {
    this->name = name;
}

bool NameFilter::evaluate(const IceCream& icecream) const {
    // O(1)
    return icecream.getNAME() == name;
}

AndFilter::AndFilter(shared_ptr<Filter> f1, shared_ptr<Filter> f2) {
    this->filter1 = f1;
    this->filter2 = f2;
}

bool AndFilter::evaluate(const IceCream& icecream) const {
    // O(1)
    return filter1->evaluate(icecream) && filter2->evaluate(icecream);
}

OrFilter::OrFilter(shared_ptr<Filter> f1, shared_ptr<Filter> f2) {
    this->filter1 = f1;
    this->filter2 = f2;
}

bool OrFilter::evaluate(const IceCream& icecream) const {
    // O(1)
    return filter1->evaluate(icecream) || filter2->evaluate(icecream);
}