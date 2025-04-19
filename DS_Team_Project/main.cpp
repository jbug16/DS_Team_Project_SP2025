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

    // Create graph from csv inputs
    graph.buildGraph(path);
    graph.printGraph();
}