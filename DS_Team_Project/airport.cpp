#include "airport.h"
#include <iostream>
using namespace std;

Airport::Airport()
{
    index = 0;
    name = "";
    city = "";
    state = "";
    visited = false;
}

Airport::Airport(int val, const string& n, const string& c, const string& s, bool v)
{
    index = val;
    name = n;
    city = c;
    state = s;
    visited = v;
}

int Airport::getIndex() const
{
    return index;
}

string Airport::getName() const
{
    return name;
}

string Airport::getCity() const
{
    return city;
}

string Airport::getState() const
{
    return state;
}

bool Airport::getVisited() const
{
    return visited;
}

void Airport::setCity(const string& c)
{
    city = c;
}

void Airport::setState(const string &s)
{
    state = s;
}

void Airport::setVisited(bool v)
{
    visited = v;
}