#include <iostream>

#include <fstream>
#include <sstream>

// Header files
#include "graph.h"

using namespace std;

// Read the data from the csv file
void loadGraphFromCSV(const string& filename, Graph& graph)
{
    ifstream file(filename);

    // Check if the file was opened successfully
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << filename << "\n";
        return;
    }

    string line;
    getline(file, line); // Skip header

    // Read the rest of the file
    while (getline(file, line))
    {
        stringstream ss(line);
        string from_airport, to_airport, from_city, to_city, distanceStr, costStr;

        getline(ss, from_airport, ',');
        getline(ss, to_airport, ',');

        // Handle quoted city fields that may contain commas
        if (line.find('"') != string::npos)
        {
            getline(ss, from_city, '"'); // skip up to first quote
            getline(ss, from_city, '"'); // get quoted city
            ss.ignore(1); // skip comma

            getline(ss, to_city, '"'); // skip to quote
            getline(ss, to_city, '"');
            ss.ignore(1); // skip comma
        }
        else
        {
            getline(ss, from_city, ',');
            getline(ss, to_city, ',');
        }

        getline(ss, distanceStr, ',');
        getline(ss, costStr, ',');

        // Convert distance and cost to doubles
        try
        {
            double distance = stod(distanceStr);
            double cost = stod(costStr);

            cout << from_airport << " " << to_airport << " " << distance << " " << cost << endl; // test output
        }
        catch (const invalid_argument& e)
        {
            cerr << "Invalid number format in line: " << line << endl;
        }
    }

    file.close();
}

int main()
{
    // Get the input from the csv
    const string path = "C:/Users/jenna/Desktop/school/SP25/DS_Team_Project_SP2025/DS_Team_Project/airports.csv";
    Graph graph;
    loadGraphFromCSV(path, graph);
}