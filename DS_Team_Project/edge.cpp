#include <edge.h>

Edge::Edge(Node* dest, double d, double c)
{
    to = dest;
    distance = d;
    cost = c;
}