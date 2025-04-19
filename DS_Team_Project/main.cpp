// Header files
#include "graph.h"
#include "flight.h"
#include <iostream>
using namespace std;

int main()
{
    // Define necessary variables
    const string path = "C:/Users/jenna/Desktop/school/SP25/DS_Team_Project_SP2025/DS_Team_Project/airports.csv";
    Graph graph;


    // ===================
    // TASK 1: Create graph from csv inputs
    // ===================

    graph.buildGraph(path);
    graph.printGraph();

    // ===================
    // TASK 2: Find the shortest path between two airports
    // ===================

    string originCode = "IAD";
    string destinationCode = "MIA";

    // Look up airport indices
    int originIndex = graph.findAirportIndex(originCode);
    int destinationIndex = graph.findAirportIndex(destinationCode);

    // Validate input
    if (originIndex == -1 || destinationIndex == -1) { cout << "Error: One or both airport codes not found in the graph.\n"; return 1; }

    // Retrieve Airport objects
    Airport* originAirport = graph.getAirportFromIndex(originIndex);
    Airport* destinationAirport = graph.getAirportFromIndex(destinationIndex);

    // Run Dijkstra's algorithm
    graph.dijkstraShortestPath(*originAirport, *destinationAirport);

    // ===================
    // TASK 3: Find all shortest paths from the origin airport to all airports in a given destination state
    // ===================



    // ===================
    // TASK 4: Find the shortest path between the origin and destination airport with a given number of stops
    // ===================



    // ===================
    // TASK 5: Print the total number of direct flight connections to each airport
    // ===================



    // ===================
    // TASK 6: Create an undirected graph from the original directed graph
    // ===================



    // ===================
    // TASK 7: Generate a Minimum Spanning Tree using Prim’s algorithm
    // ===================



    // ===================
    // TASK 8: Generate a Minimum Spanning Tree using Kruskal’s algorithm
    // ===================

    

    return 0;
}