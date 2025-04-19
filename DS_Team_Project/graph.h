#ifndef GRAPH_H
#define GRAPH_H

#include "airport.h"
#include <iostream>
#include <vector>
class Airport;
class Flight;
using namespace std;

// Store the results if the Dijkstra algorithm
struct DijkstraResult
{
    vector<double> distances; // distances of the flights
    vector<double> costs; // costs of the flights
    vector<int> previous; // the previous airport (this is for indirect flights ex. ATL -> JFK -> MCO)
};

class Graph
{
    vector<Airport*> airports;
    vector<Flight*> adjList;
    int airportCount;

public:
    Graph(); // default constructor

    // Functions to add airports (nodes) and flights (edges)
    void addAirport(const string& name, const string& city, const string& state);
    void addFlight(const string& from, const string& fromCity, const string& fromState, const string& to, const string& toCity, const string& toState, double distance, double cost);

    // Lookup functions to check existing data
    int findAirportIndex(const string& name) const;

    Airport* getAirportFromIndex(int index) const;
    bool airportExists(const string& name) const;

    // Function to build the graph
    void buildGraph(const string& filename);

    // Function to output the graph
    void printGraph() const;

    // Function to collect all the flights into one list
    vector<Flight*> getAllFlights() const;

    // Algorithm functions
    void DFS(Airport& airport);
    void BFS(Airport& airport);
    DijkstraResult dijkstra(const Airport& fromAirport, const Airport& toAirport); // I've put it into its own function, so I can use it multiple times for each different task (when needed)

    // Task functions
    void shortestPath(const Airport& fromAirport, const Airport& toAirport); // TASK 2
    void shortestPathsToState(const Airport& fromAirport, const string& toState); // TASK 3

    // Helpers
    void cleanVisited() const;
    void DFSHelper(Airport& airport);
};

#endif
