#include "edge.h"

Edge::Edge(Airport* dest, double d, double c)
{
    to = dest;
    distance = d;
    cost = c;
}