#ifndef GRAPH_H
#define GRAPH_H

#include <airport.h>
#include <iostream>
#include <vector>
class Airport;
class Flight;
using namespace std;

const int MAX_AIRPORTS = 200;

class Graph
{
    vector<Airport*> airports;
    vector<Flight*> adjList;
    int airportCount;

public:
    Graph(); // default constructor

    // Functions to add airports (nodes) and flights (edges)
    void addAirport(const string& name);
    void addFlight(const string& from, const string& to, double distance, double cost);

    // Lookup functions to check existing data
    int findAirportIndex(const string& name) const;
    bool airportExists(const string& name) const;

    // Function to build the graph
    void buildGraph(const string& filename);

    // Function to output the graph
    void printGraph() const;

    // Function to collect all the flights into one list
    vector<Flight*> getAllFlights() const;

    // Search functions
    void DFS(Airport& airport);
    void BFS(Airport& airport);
    int dijkstraShortestPath(const Airport& fromAirport, const Airport& toAirport);

    void cleanVisited();
    void DFSHelper(Airport& airport);
};

#endif
