#include "graph.h"
#include "airport.h"
#include "flight.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Graph::Graph()
{
    airportCount = 0;
}

void Graph::addAirport(const string& name)
{
    // Check if the airport is already in the list
    if (!airportExists(name))
    {
        // If not,
        // Create the new airport
        auto newAirport = new Airport(airportCount, name, false);
        // Add it to the list
        airports.push_back(newAirport);
        // Add an empty flight to the adjList
        adjList.push_back(nullptr);
        // Update the count of airports
        airportCount++;
    }
}

bool Graph::airportExists(const string& name) const
{
    // Loop through all the airports in the list
    for (int i = 0; i < airportCount; i++)
    {
        // Return true if there is an airport in the list with the same name
        if (airports[i]->getName() == name)
        {
            return true;
        }
    }
    return false;
}

int Graph::findAirportIndex(const string &name) const
{
    // Loop through all the airports
    for (int i = 0; i < airportCount; i++)
    {
        // Get the index of the current airport
        if (airports[i]->getName() == name)
        {
            return i;
        }
    }
    return -1;
}

void Graph::addFlight(const string& from, const string& to, double distance, double cost)
{
    int fromIndex = findAirportIndex(from);
    int toIndex = findAirportIndex(to);

    if (fromIndex == -1)
    {
        addAirport(from);
        fromIndex = airportCount - 1;
    }

    if (toIndex == -1)
    {
        addAirport(to);
        toIndex = airportCount - 1;
    }

    Airport* destAirport = airports[toIndex];
    auto newFlight = new Flight(destAirport, distance, cost);
    newFlight->fromIndex = fromIndex;

    // Link into the beginning of the linked list
    newFlight->setNext(adjList[fromIndex]);
    adjList[fromIndex] = newFlight;
}

void Graph::buildGraph(const string& filename)
{
    cout << "Building graph..." << endl;

    // Read the data from the csv file
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

        try
        {
            double distance = stod(distanceStr);
            double cost = stod(costStr);

            // Add airports if not already added
            if (!airportExists(from_airport)) addAirport(from_airport);
            if (!airportExists(to_airport)) addAirport(to_airport);

            // Add the flight (edge)
            addFlight(from_airport, to_airport, distance, cost);
        }
        catch (const invalid_argument& e)
        {
            cerr << e.what() << endl;
            cerr << "Skipping invalid line: " << line << endl;
        }
    }

    file.close();
}

void Graph::printGraph() const
{
    cout << "Flight Graph:\n";

    for (int i = 0; i < airportCount; i++)
    {
        cout << airports[i]->getName() << " -> ";

        Flight* current = adjList[i];
        while (current != nullptr)
        {
            cout << current->getDestination()->getName()
                 << " (Dist: " << current->getDistance()
                 << ", Cost: " << current->getCost() << ") -> ";
            current = current->getNext();
        }

        cout << "null\n";
    }
}

vector<Flight *> Graph::getAllFlights() const
{
    vector<Flight*> flights;

    for (int i = 0; i < airportCount; i++)
    {
        Flight* current = adjList[i];
        while (current != nullptr)
        {
            flights.push_back(current);
            current = current->getNext();
        }
    }

    return flights;
}
