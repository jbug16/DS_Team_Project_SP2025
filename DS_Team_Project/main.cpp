#include <iostream>

#include <fstream>
#include <sstream>

// Header files
#include "graph.h"

using namespace std;

void loadGraphFromCSV(const string& filename, Graph& graph)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line))
    {
        stringstream ss(line);
        string from, to, distanceStr, costStr;

        getline(ss, from, ',');
        getline(ss, to, ',');
        getline(ss, distanceStr, ',');
        getline(ss, costStr, ',');

        double distance = stod(distanceStr);
        double cost = stod(costStr);

        cout << from << " " << to << " " << distance << endl;
    }

    file.close();
}

int main()
{
    // get the input from the csv
    Graph graph;
    loadGraphFromCSV("airports.csv", graph);
}