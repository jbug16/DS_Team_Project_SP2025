#include "graph.h"

#include <algorithm>

#include "airport.h"
#include "flight.h"
#include "minheap.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

Graph::Graph()
{
    airportCount = 0;
}

void Graph::addAirport(const string& name, const string& city, const string& state)
{
    // Check if the airport is already in the list
    if (!airportExists(name))
    {
        // If not,
        // Create the new airport
        auto newAirport = new Airport(airportCount, name, city, state, false);
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

Airport* Graph::getAirportFromIndex(int index) const
{
    return airports[index];
}

void Graph::addFlight(const string& from, const string& fromCity, const string& fromState, const string& to, const string& toCity, const string& toState, double distance, double cost)
{
    int fromIndex = findAirportIndex(from);
    int toIndex = findAirportIndex(to);

    if (fromIndex == -1)
    {
        addAirport(from, fromCity, fromState);
        fromIndex = airportCount - 1;
    }

    if (toIndex == -1)
    {
        addAirport(to, toCity, toState);
        toIndex = airportCount - 1;
    }

    Airport* destAirport = airports[toIndex];
    auto newFlight = new Flight(destAirport, distance, cost);
    newFlight->fromIndex = fromIndex;

    // Link into the beginning of the linked list
    newFlight->setNext(adjList[fromIndex]);
    adjList[fromIndex] = newFlight;
}

// Helper Trim function because C++ is mean and doesn't have one :(((
string trim(const string& str)
{
    size_t start = 0;
    while (start < str.length() && isspace(str[start])) start++;

    size_t end = str.length();
    while (end > start && isspace(str[end - 1])) end--;

    return str.substr(start, end - start);
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
        string from_airport, to_airport;
        string from_city, to_city, from_city_raw, to_city_raw;
        string from_state, to_state;
        string distanceStr, costStr;

        getline(ss, from_airport, ',');
        getline(ss, to_airport, ',');

        // Handle quoted city fields
        if (line.find('"') != string::npos)
        {
            getline(ss, from_city_raw, '"'); // skip up to quote
            getline(ss, from_city_raw, '"'); // get "City, ST"
            ss.ignore(1); // skip comma

            getline(ss, to_city_raw, '"');
            getline(ss, to_city_raw, '"');
            ss.ignore(1); // skip comma
        }
        else
        {
            getline(ss, from_city_raw, ',');
            getline(ss, to_city_raw, ',');
        }

        // Split by comma to get city and state
        stringstream fromSplit(from_city_raw);
        getline(fromSplit, from_city, ',');
        getline(fromSplit, from_state);

        stringstream toSplit(to_city_raw);
        getline(toSplit, to_city, ',');
        getline(toSplit, to_state);

        getline(ss, distanceStr, ',');
        getline(ss, costStr, ',');

        try
        {
            double distance = stod(distanceStr);
            double cost = stod(costStr);

            stringstream fromSplit(from_city_raw);
            getline(fromSplit, from_city, ',');
            getline(fromSplit, from_state);
            from_state = trim(from_state); // remove space

            stringstream toSplit(to_city_raw);
            getline(toSplit, to_city, ',');
            getline(toSplit, to_state);
            to_state = trim(to_state); // remove space


            // Add airports if not already added
            if (!airportExists(from_airport)) addAirport(from_airport, from_city, from_state);
            if (!airportExists(to_airport)) addAirport(to_airport, to_city, to_state);

            // Add the flight (edge)
            addFlight(from_airport, from_city, from_state, to_airport, to_city, to_state, distance, cost);
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

vector<Flight*> Graph::getAllFlights() const
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

void Graph::cleanVisited() const
{
    for (int i = 0; i < airportCount; i++)
    {
        airports[i]->setVisited(false);
    }
}

// Dijkstra functions
DijkstraResult Graph::dijkstra(const Airport &fromAirport, const Airport &toAirport)
{
    // Base function used from canvas (with some modifications)
    DijkstraResult result;

    int i_src = findAirportIndex(fromAirport.getName());
    int i_dest = findAirportIndex(toAirport.getName());

    result.distances.resize(airportCount, INT_MAX);
    result.costs.resize(airportCount, INT_MAX);
    result.previous.resize(airportCount, -1);

    // Airports do not exist
    if (i_src == -1 || i_dest == -1)
    {
        throw string("Shortest path: incorrect airports");
        return result;
    }

    cleanVisited();

    result.distances[i_src] = 0;
    result.costs[i_src] = 0;

    MinHeap<Flight*> heap;
    airports[i_src]->setVisited(true);

    // Push all initial neighbors from the source
    Flight* current = adjList[i_src];
    while (current != nullptr)
    {
        int destIndex = current->getDestination()->getIndex();

        result.distances[destIndex] = current->getDistance();
        result.costs[destIndex] = current->getCost();
        result.previous[destIndex] = i_src;

        heap.insert(current);
        current = current->getNext();
    }

    while (!heap.empty())
    {
        Flight* f = heap.delete_min();
        int from = f->fromIndex;
        int to = f->getDestination()->getIndex();

        if (!airports[to]->getVisited())
        {
            airports[to]->setVisited(true);

            Flight* neighbor = adjList[to];
            while (neighbor != nullptr)
            {
                int neighborIndex = neighbor->getDestination()->getIndex();
                double newDist = result.distances[to] + neighbor->getDistance();
                double newCost = result.costs[to] + neighbor->getCost();

                if (newDist < result.distances[neighborIndex])
                {
                    result.distances[neighborIndex] = newDist;
                    result.costs[neighborIndex] = newCost;
                    result.previous[neighborIndex] = to; // track where previous node came from
                    heap.insert(neighbor);
                }
                neighbor = neighbor->getNext();
            }
        }
    }

    cleanVisited();
    return result;
}

void Graph::shortestPath(const Airport& fromAirport, const Airport& toAirport)
{
    // Get results from the dijkstra algorithm
    DijkstraResult result = dijkstra(fromAirport, toAirport);

    int i_dest = findAirportIndex(toAirport.getName()); // index of destination

    // No path found
    if (i_dest == -1 || result.distances[i_dest] == INT_MAX)
    {
        cout << "Shortest route from " << fromAirport.getName() << " to " << toAirport.getName() << ": None";
        return;
    }

    // Reconstruct path
    vector<string> path;
    int currentIndex = i_dest;
    while (currentIndex != -1)
    {
        path.push_back(airports[currentIndex]->getName());
        currentIndex = result.previous[currentIndex];
    }

    vector<string> reversedPath;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        reversedPath.push_back(path[i]);
    }

    // Print path
    cout << "Shortest route from " << fromAirport.getName() << " to " << toAirport.getName() << ": ";
    for (int i = 0; i < reversedPath.size(); i++)
    {
        cout << reversedPath[i];
        if (i < reversedPath.size() - 1) cout << " -> ";
    }
    cout << ". The length is " << result.distances[i_dest] << ". The cost is " << result.costs[i_dest] << "." << endl;
}

void Graph::shortestPathsToState(const Airport& fromAirport, const string& toState)
{
    DijkstraResult result = dijkstra(fromAirport, fromAirport); // destination param doesn't matter

    cout << "Shortest paths from " << fromAirport.getName() << " to " << toState << " state airports are:\n\n";
    cout << "Path\t\t\tLength\tCost" << endl;

    for (int i = 0; i < airportCount; i++)
    {
        Airport* ap = airports[i];

        // Skip if not in target state or not reachable
        if (ap->getState() != toState || result.distances[i] == INT_MAX) continue;

        // Reconstruct path
        vector<string> path;
        int currentIndex = i;
        while (currentIndex != -1)
        {
            path.push_back(airports[currentIndex]->getName());
            currentIndex = result.previous[currentIndex];
        }

        // Manually reverse path
        vector<string> reversedPath;
        for (int j = path.size() - 1; j >= 0; j--)
        {
            reversedPath.push_back(path[j]);
        }

        // Print path
        for (int j = 0; j < reversedPath.size(); j++)
        {
            cout << reversedPath[j];
            if (j < reversedPath.size() - 1) cout << " -> ";
        }

        // Print length and cost
        cout << "\t" << result.distances[i] << "\t" << result.costs[i] << endl;
    }
}

void Graph::DFS(int currentIndex, int destIndex, int stopsRemaining, double currentDist, double currentCost, vector<string> &currentPath, double &bestDist, double &bestCost, vector<string> &bestPath)
{
    currentPath.push_back(airports[currentIndex]->getName());

    if (stopsRemaining == 0)
    {
        if (currentIndex == destIndex)
        {
            if (currentDist < bestDist)
            {
                bestDist = currentDist;
                bestCost = currentCost;
                bestPath = currentPath;
            }
        }

        currentPath.pop_back();
        return;
    }

    Flight* flight = adjList[currentIndex];
    while (flight != nullptr)
    {
        int next = flight->getDestination()->getIndex();

        DFS(next, destIndex, stopsRemaining - 1, currentDist + flight->getDistance(), currentCost + flight->getCost(), currentPath, bestDist, bestCost, bestPath);

        flight = flight->getNext();
    }

    currentPath.pop_back();
}


void Graph::shortestPathsWithStops(const Airport& fromAirport, const Airport& toAirport, int stops)
{
    // We use DFS in this function!

    int i_src = findAirportIndex(fromAirport.getName()); // index of source
    int i_dest = findAirportIndex(toAirport.getName()); // index of destination

    if (i_src == -1 || i_dest == -1)
    {
        cout << "Invalid airport code." << endl;
        return;
    }

    vector<string> currentPath;
    vector<string> bestPath;
    double bestDist = INT_MAX;
    double bestCost = INT_MAX;

    DFS(i_src, i_dest, stops+1, 0, 0, currentPath, bestDist, bestCost, bestPath);

    // Print path, distance and cost (if there is one with this many stops)
    cout << "Shortest route from " << fromAirport.getName() << " to " << toAirport.getName() << " with " << stops << " stops: ";

    if (bestPath.empty())
    {
        cout << "None" << endl;
        return;
    }

    for (int i = 0; i < bestPath.size(); i++)
    {
        cout << bestPath[i];
        if (i < bestPath.size() - 1) cout << " -> ";
    }

    cout << ". The length is " << bestDist << ". The cost is " << bestCost << "." << endl;
}

void Graph::countDirectConnections() const
{
    vector<pair<string, int>> airportConnections; // this stores the airport name and total connection count

    // For each airport...
    for (int i = 0; i < airportCount; i++)
    {
        int inbound = 0;
        int outbound = 0;

        // Count how many flights go into this airport
        Flight* flight = adjList[i];
        while (flight != nullptr)
        {
            outbound++;
            flight = flight->getNext();
        }

        // Count how many flights it sends out
        for (int j = 0; j < airportCount; j++)
        {
            if (j == i) continue; // skip itself

            Flight* otherFlight = adjList[j];
            while (otherFlight != nullptr)
            {
                if (otherFlight->getDestination()->getIndex() == i) inbound++; // checks if the flight goes to that airport index
                otherFlight = otherFlight->getNext();
            }
        }

        int totalCount = inbound + outbound;
        airportConnections.push_back({airports[i]->getName(), totalCount}); // add connections to list
    }

    // Sort the list by connection count (descending order)
    sort(airportConnections.begin(), airportConnections.end(),
     [](pair<string, int>& a, pair<string, int>& b) {
         return a.second > b.second;
     });

    // Print
    cout << "Airport\t\tConnections" << endl;
    for (int i = 0; i < airportConnections.size(); i++)
    {
        cout << airportConnections[i].first << "\t\t" << airportConnections[i].second << endl;
    }
}
