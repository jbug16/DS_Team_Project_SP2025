#include "flight.h"
#include "airport.h"

Flight::Flight()
{
    to = nullptr;
    distance = 0;
    cost = 0;
    next = nullptr;
}

Flight::Flight(Airport* dest, double d, double c)
{
    to = dest;
    distance = d;
    cost = c;
    next = nullptr;
}

Airport *Flight::getDestination() const
{
    return to;
}

double Flight::getDistance() const
{
    return distance;
}

double Flight::getCost() const
{
    return cost;
}

Flight *Flight::getNext() const
{
    return next;
}

void Flight::setNext(Flight *n)
{
    next = n;
}