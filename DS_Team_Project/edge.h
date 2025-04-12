//
// Created by jenna on 4/12/2025.
//

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <node.h>
using namespace std;

class Edge {
    Node* to;
    double distance;
    double cost;

    Edge(Node* dest, double d, double c) : to(dest), distance(d), cost(c) {}
};

#endif //EDGE_H
