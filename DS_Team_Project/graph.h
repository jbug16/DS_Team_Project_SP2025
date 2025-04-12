#ifndef GRAPH_H
#define GRAPH_H

#include "airport.h"
#include "edge.h"
#include <vector>

class Graph {
private:
    struct Node {
        Airport airport;
        vector<Edge> edges;
    };

    vector<Node> adjacencyList;

public:
    Graph();

    void addAirport(const Airport& ap);
    void addFlight(string origin, const Edge& edge);

    int findAirportIndex(string code) const;
    bool airportExists(string code) const;

    void printGraph() const;
    
};

#endif
