#ifndef PROIECTOOP_FILTER_H
#define PROIECTOOP_FILTER_H

#include <memory>
#include "../Domain/IceCream.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual bool evaluate(const IceCream& icecream) const = 0;
};

class FlavourFilter : public Filter {
private:
    string flavour;
public:
    FlavourFilter(const string& flavour);
    bool evaluate(const IceCream& icecream) const override;
};

class NameFilter : public Filter {
private:
    string name;
public:
    NameFilter(const string& name);
    bool evaluate(const IceCream& icecream) const override;
};

class AndFilter : public Filter {
private:
    shared_ptr<Filter> filter1;
    shared_ptr<Filter> filter2;
public:
    AndFilter(shared_ptr<Filter> f1, shared_ptr<Filter> f2);
    bool evaluate(const IceCream& icecream) const override;
};

class OrFilter : public Filter {
private:
    shared_ptr<Filter> filter1;
    shared_ptr<Filter> filter2;
public:
    OrFilter(shared_ptr<Filter> f1, shared_ptr<Filter> f2);
    bool evaluate(const IceCream& icecream) const override;
};

#endif