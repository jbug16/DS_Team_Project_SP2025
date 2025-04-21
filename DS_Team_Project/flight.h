#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
using namespace std;
class Airport;

class Flight
{
    Airport* to; // the airport that the flight is going to
    double distance; // the distance of the flight
    double cost; // the cost of the flight
    Flight* next; // pointer to the next flight in the list

public:
    Flight(); // default constructor
    Flight(Airport* dest, double d, double c); // constructor defining destination, distance and cost

    int fromIndex; // index of the airport from

    // Getters
    Airport* getDestination() const;
    double getDistance() const;
    double getCost() const;
    Flight* getNext() const;

    // Setters
    void setNext(Flight* next);
};

#endif //FLIGHT_H