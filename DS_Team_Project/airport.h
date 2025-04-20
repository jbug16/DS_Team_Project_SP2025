//
// Created by jenna on 4/12/2025.
//

#ifndef AIRPORT_H
#define AIRPORT_H

#include <iostream>
using namespace std;

class Airport
{
    int index;
    string name;
    string city;
    string state;
    bool visited;

public:
    Airport(); // default constructor
    Airport(int val, const string& n, const string& c, const string& s, bool v); // constructor defining the index and name of the airport

    // Getters
    int getIndex() const;
    string getName() const;
    string getCity() const;
    string getState() const;
    bool getVisited() const;

    // Setters
    void setCity(const string& c);
    void setState(const string& s);
    void setVisited(bool visited);
};

#endif //AIRPORT_H