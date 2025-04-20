// Header files
#include "graph.h"
#include "flight.h"
#include <iostream>
using namespace std;

int main()
{
    const string path = "C:/Users/jenna/Desktop/school/SP25/DS_Team_Project_SP2025/DS_Team_Project/airports.csv";
    Graph graph;

    // ===================
    // TASK 1: Create graph from csv inputs
    // ===================

    cout << "TASK 1" << endl;
    graph.buildGraph(path);
    cout << "Graph has been built." << endl;

    // Needed for next tasks
    string originCode = "IAD"; // this is the "from airport"
    string destinationCode = "MIA"; // this is the "to airport"
    int originIndex = graph.findAirportIndex(originCode); // index of the "from airport"
    int destinationIndex = graph.findAirportIndex(destinationCode); // index of the "to airport"
    Airport* originAirport = graph.getAirportFromIndex(originIndex); // from airport object
    Airport* destinationAirport = graph.getAirportFromIndex(destinationIndex); // to airport object

    // ===================
    // TASK 2: Find the shortest path between two airports
    // ===================

    cout << "\nTASK 2" << endl;
    graph.shortestPath(*originAirport, *destinationAirport);

    // ===================
    // TASK 3: Find all shortest paths from the origin airport to all airports in a given destination state
    // ===================

    cout << "\nTASK 3" << endl;
    graph.shortestPathsToState(*originAirport, "FL");

    // ===================
    // TASK 4: Find the shortest path between the origin and destination airport with a given number of stops
    // ===================

    cout << "\nTASK 4" << endl;
    graph.shortestPathsWithStops(*originAirport, *destinationAirport, 1);

    // ===================
    // TASK 5: Print the total number of direct flight connections to each airport
    // ===================

    cout << "\nTASK 5" << endl;
    graph.countDirectConnections();

    // ===================
    // TASK 6: Create an undirected graph from the original directed graph
    // ===================
    cout << "\nTASK 6" << endl;;
    graph.buildUndirectedGraph();
    cout << "Undirected Graph has been built." << endl;


    // ===================
    // TASK 7: Generate a Minimum Spanning Tree using Prim’s algorithm
    // ===================



    // ===================
    // TASK 8: Generate a Minimum Spanning Tree using Kruskal’s algorithm
    // ===================



    return 0;
}