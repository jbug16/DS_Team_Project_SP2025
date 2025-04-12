//
// Created by jenna on 4/12/2025.
//

#ifndef EDGE_H
#define EDGE_H

#include "airport.h"
using namespace std;

class Edge {
    Airport* to;
    double distance;
    double cost;

    Edge(Airport* dest, double d, double c);
};

#endif //EDGE_H
